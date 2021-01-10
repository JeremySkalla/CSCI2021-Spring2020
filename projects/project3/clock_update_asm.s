## JEREMY SKALLA

.text
.global  set_tod_from_secs

## ENTRY POINT FOR REQUIRED FUNCTION
set_tod_from_secs:
    # %edi is int argument, %rsi is pointer argument (tod_t in c)

    cmpl    $86400,%edi                     # next four lines are making sure input is inbounds
    jge     .00B
    cmpl    $0,%edi
    jl      .00B

    cmpl    $43200,%edi                     # next three lines are checking for am or pm
    jge     ispm
    jl      isnotpm

    .continue:

    movl    $0,%edx                         # Setting remainder to zero
    movl    %edi,%eax                       # moving time of day into dividend
    movl    $3600,%r8d                      # sets divisor to 3600
    cqto
    idivl   %r8d                            # dividing time of day into hours
    movw    %ax,(%rsi)                      # sets hours
    cmpl    $0,%eax
    je      zerohour                        # if hours is 0
    .afterzerohour:

    movl    %edx,%eax                       # moves remainder of hours into dividend
    movl    $60,%r8d                        # sets divisor to 60
    cqto
    idivl   %r8d                            # divides time of day into minutes
    movw    %ax,2(%rsi)                     # sets minutes

    movw    %dx,4(%rsi)                     # sets seconds (remainder)

    movl    $0, %eax
    ret

.00B:
    ## ERROR
    movl    $1,%eax
    ret

ispm:
    movb    $1,6(%rsi)                      # moves 1 into ispm
    subl    $43200,%edi                     # subtracts 12 hours in seconds from time of day in seconds
    jmp     .continue

isnotpm:
    movb    $0,6(%rsi)                      # moves 0 into ispm
    jmp     .continue

zerohour:
    movw    $12,(%rsi)
    jmp     .afterzerohour


### Data area associated with the next function
.data

am_int:                         # for when am
        .int 0b0000001          # value 1

pm_int:                      # for when pm
        .int 0b0000010          # value 2

third_int:                      # for when hour tens is 0
        .int 0b0000000          # value 0

my_array:                       # declare multiple ints in a row
        .int 0b0111111          # for an array. Each are spaced
        .int 0b0000110          # 4 bytes from each other
        .int 0b1011011
        .int 0b1001111
        .int 0b1100110
        .int 0b1101101
        .int 0b1111101
        .int 0b0000111
        .int 0b1111111
        .int 0b1101111

.text
.global  set_display_bits_from_tod

## ENTRY POINT FOR REQUIRED FUNCTION
set_display_bits_from_tod:
    # %rdi is tod, %rsi is int display pointer in binary

    pushq %rdi                              # Push rdi onto the stack

    cmpw    $12,(%rsp)                      # next twelve lines are making sure input is inbounds
    jg      .01B
    cmpw    $0,(%rsp)
    jle     .01B
    cmpw    $60,2(%rsp)
    jge      .01B
    cmpw    $0,2(%rsp)
    jl      .01B
    cmpw    $60,4(%rsp)
    jge      .01B
    cmpw    $0,4(%rsp)
    jl      .01B


    leaq my_array(%rip), %r12               # load array into the program into %r12

    # %cx is minute ones, %r8w is minute tens, %r9w is hour ones, %r10w is hour tens, %r11b is am or pm
    # %r13d is divisor
    movl    2(%rsp),%eax                    # Move minutes into dividend
    andq    $0xFFFF,%rax
    cqto
    movl    $10,%r13d
    idivl   %r13d                           # Dividing minutes by 10
    movl    %edx,%ecx                       # Sets minute ones to remainder
    andq    $0xFFFF,%rcx                    # Only using bottom two bytes
    movl    (%r12,%rcx,4),%ecx              # Sets minute ones to analog digit in binary

    movl    %eax,%r8d                       # Sets minute tens to quotient
    andq    $0xFFFF,%r8
    movl    (%r12,%r8,4),%r8d               # Sets minute tens to analog digit in binary

    movl    (%rsp),%eax                     # Move hours into dividend
    andq    $0xFFFF,%rax


    movl    $10,%r13d
    cqto
    idivl   %r13d                           # Dividing hours by 10
    movl    %edx,%r9d                       # Sets hour ones to remainder
    andq    $0xFFFF,%r9
    movl    (%r12,%r9,4),%r9d               # Sets hour ones to analog digit in binary

    movl    %eax,%r10d                      # Sets hour tens to quotient
    andq    $0xFFFF,%r10

    cmpq    $0,%r10
    je      hourtenzero                     # If the hour tens spot is zero
    jne     hourtenone                      # If the hour tens spot is one

    .afterhourtens:

    cmpb    $1,6(%rsp)
    je      ifpm                            # If it is pm
    jne     ifam                            # If it is am

    .afterampm:

    movl    $0,(%rsi)                       # Set display to zero

    shll    $7,%r8d                         # Shift min tens 7 bits left
    shll    $14,%r9d                        # Shift hour ones 14 bits left
    shll    $21,%r10d                       # Shift hour tens 21 bits left
    shll    $28,%r11d                       # Shift am or pm 28 bits left

    orl     %ecx,(%rsi)                     # Or with min ones
    orl     %r8d,(%rsi)                     # Or with min tens
    orl     %r9d,(%rsi)                     # Or with hour ones
    orl     %r10d,(%rsi)                    # Or with hour tens
    orl     %r11d,(%rsi)                    # Or with am/pm

    popq    %rdi                            # pop rdi off the stack

    movl    $0,%eax
    ret

.01B:
    ## ERROR
    popq %rdi                               # pop rdi off the stack
    movl    $1,%eax
    ret

hourtenzero:
    movl    third_int(%rip),%r10d
    jmp     .afterhourtens

hourtenone:
    movl    $0b0000110,%r10d
    jmp     .afterhourtens

ifam:
    movb    am_int(%rip),%r11b
    jmp     .afterampm

ifpm:
    movb    pm_int(%rip),%r11b
    jmp     .afterampm
.text
.global clock_update

## ENTRY POINT FOR REQUIRED FUNCTION
clock_update:
    pushq   $0                              # Establishes "zero" tod
    movq    %rsp,%rsi                       # Copies zero tod into %rsi register
    movl    TIME_OF_DAY_SEC(%rip),%edi      # Copies global variable into %edi register
    call    set_tod_from_secs               # Calls function using %edi and %rsi

    cmpl    $1,%eax
    je      .02B                            # If error with set_tod function

    movq    (%rsp),%rdi                     # Copies tod into %rdi register

    leaq    CLOCK_DISPLAY_PORT(%rip),%rsi   # CLOCK_DISPLAY_PORT into %rsi register
    call    set_display_bits_from_tod       # Calls function using %rdi and %rsi

    cmpl    $1,%eax
    je      .02B                            # If error with set_display function

    popq    %r8

    movl    $0,%eax
    ret

.02B:
    ## ERROR
    popq    %r8
    movl    $1,%eax
    ret
