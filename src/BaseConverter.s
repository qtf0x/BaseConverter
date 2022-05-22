# @file MariasVincent_ASSEMBLY.s
# @author Vincent Marias (@vincent-marias)
# @date 2022-05-11
#
# @brief A number base converter (base [2, 36] -> base 10).

.data
    value: .space 41	# 41B (characters)
    basePrompt: .string "Please enter the base of the number you are using (0 to exit): "
    valuePrompt: .string "Please enter the value: "
    resultPrompt: .string "The given value in base 10 is: "
    errorPrompt: .string "The value entered is not valid for the base entered\n\n"
    newlines: .string "\n\n"

.text
    .globl main
    main:
        jal ra, getBase		# get the base from user
        
        beq a0, zero, mainExit	# base == 0 means exit program
        
        jal ra, getValue	# get the value from user
        
        add a2, zero, a0	# put base as argument for next method
        jal ra, translateValue
        
        beq a1, zero, mainCleanPrint	# error flag was not set by translateValue
        bne a1, zero, mainErrorPrint	# error falg was set by translateValue
        
        mainErrorPrint:
            addi a7, zero, 4	# PrintString syscall
            la a0, errorPrompt	# load address of error prompt
            ecall
            
            jal zero, main		# keep looping until base == 
        
        mainCleanPrint:
            add a1, zero, a0	# put result as argument for next method
            jal ra, printResult
            jal zero, main		# keep looping until base == 0
        
        mainExit:
            addi a7, zero, 10	# Exit syscall
            ecall

    # Arguments
    #	None
    # Return values
    #	a0: base chosen
    .globl getBase
    getBase:
        addi t0, zero, -1	# only negative to start loop
        addi t1, zero, 2	# minimum valid base
        addi t2, zero, 37	# maximum valid base (+1 for bge)
        
        getBaseLoop:
            addi a7, zero, 4	# PrintString syscall
            la a0, basePrompt	# load address of basePrompt
            ecall
        
            addi a7, zero, 5	# ReadInt syscall
            ecall
            add t0, zero, a0	# put read int into t0
            
            beq t0, zero, getBaseExit	# exit if 0 entered
            blt t0, t1, getBaseLoop		# loop again if entered val < min
            bge t0, t2, getBaseLoop		# loop again if entered val > max
            
        getBaseExit:
            add a0, zero, t0	# save return value
            
            jalr zero, ra, 0
    
    # Arguments
    #	None
    # Return values
    #	None
    .globl getValue
    getValue:
        addi sp, sp, -4		# adjust stack for 1 item
        sw a0, 0(sp)		# save a0
        
        addi a7, zero, 4	# PrintString syscall
        la a0, valuePrompt	# load address of valuePrompt
        ecall
        
        addi a7, zero, 8	# ReadString syscall
        la a0, value		# load address of value
        addi a1, zero, 42	# read 41 chars max (with \n)
        ecall
        
        lw a0, 0(sp)		# restore a0
        addi sp, sp, 4		# readjust stack
        
        jalr zero, ra, 0
    
    # Arguments
    #	a1: value after translation
    # Return values
    #	None
    .globl printResult
    printResult:
        addi a7, zero, 4	# PrintString syscall
        la a0, resultPrompt	# load address of resultPrompt
        ecall
        
        addi a7, zero, 1	# PrintInt syscall
        add a0, zero, a1	# load result for printing
        ecall
        
        addi a7, zero, 4	# PrintString syscall
        la a0, newlines	# load address of resultPrompt
        ecall
        
        jalr zero, ra, 0
    
    # Arugments
    #	a2: base to convert from
    # Return Values
    #	a0: translated value
    #	a1: error flag (1 for error)
    .globl translateValue
    translateValue:
        addi sp, sp, -4		# adjust stack for 1 item
        sw ra, 0(sp)		# save ra
    
        addi t0, zero, 1	# loop variable
        addi t1, zero, 45	# '-'
        add t2, zero, zero	# result
        
        la a1, value	# address of value to convert
        jal ra, strlen	# get the length of the value
        add a3, zero, a0	# characters to check
        add t4, zero, a0	# copy of characters to check
        
        addi a4, a3, 1	# avoid pseudoinstruction bgt
        bge t0, a4, translateValueCleanExit
        
        translateValueLoop:
            sub t4, a3, t0	# index of next char
            la a1, value	# address of value to convert
            add a1, a1, t4	# add index to address
            lb t5, 0(a1)	# char to translate
            
            bne t5, t1, translateValueNonnegative
            bne t4, zero, translateValueNonnegative
            jal zero, translateValueNegative
            
            translateValueNonnegative:
                add a1, zero, t5	# put char in argument a1
                jal ra, translateFromASCII	# translate the character
                add t3, zero, a0	# save result of translation
                
                blt t3, zero, translateValueErrorExit	# translation failed
                bge t3, a2, translateValueErrorExit		# input invalid
                
                add a5, zero, a2	# store a2 for use after
                
                add a1, zero, a2	# base
                add a2, zero, t0	# power
                addi a2, a2, -1		# adjust power
                jal ra, pow
                
                add a2, zero, a5	# restore a2
                
                mul t6, t3, a0		# value * base^power
                add t2, t2, t6		# add to result
                
                addi t0, t0, 1		# increment loop variable
                
                addi a4, a3, 1	# avoid pseudoinstruction ble
                blt t0, a4, translateValueLoop
                
                jal zero, translateValueCleanExit
        
            translateValueNegative:
                addi a0, zero, -1
                mul t2, t2, a0	# negate result
            
                jal zero, translateValueCleanExit
        
        translateValueErrorExit:
            addi a1, zero, 1	# error flag set
            
            lw ra, 0(sp)		# restore ra
            addi sp, sp, 4		# readjust stack
            
            jalr zero, ra, 0
        
        translateValueCleanExit:
            add a0, zero, t2	# save result for return
            add a1, zero, zero	# no error
            
            lw ra, 0(sp)		# restore ra
            addi sp, sp, 4		# readjust stack
            
            jalr zero, ra, 0
    
    # Arguments
    #	a1: the address of a string
    # Return values
    #	a0: the length of the string
    .globl strlen
    strlen:
        addi sp, sp, -12	# adjust stack for 3 items
        sw t0, 8(sp)		# save t0
        sw t1, 4(sp)		# save t1
        sw t2, 0(sp)		# save t2
        
        add t0, zero, zero	# loop variable
        addi t1, zero, 10	# \n character
        
        strlenLoop:
            add t2, t0, a1			# add byte offset
            lb t2, 0(t2)			# get next character
            beq t2, t1, strlenExit	# found \n
            addi t0, t0, 1			# increment loop variable
            jal zero, strlenLoop	# keep looping
        
        strlenExit:
            add a0, zero, t0	# save string length to return
            
            lw t2, 0(sp)	# restore t2
            lw t1, 4(sp)	# restore t1
            lw t0, 8(sp)	# restore t0
            addi sp, sp, 12	# readjust stack
            
            jalr zero, ra, 0
    
    # Arguments
    #	a1: base
    #	a2: power
    # Return values
    #	a0: result
    .globl pow
    pow:
        addi sp, sp, -12	# adjust stack for 3 items
        sw t0, 8(sp)		# save t0
        sw t1, 4(sp)		# save t1
        sw t2, 0(sp)		# save t2
        
        addi t1, zero, 1	# if power <= 0, result = 1
        blt a2, t1, powExit
        
        add t0, zero, zero	# loop variable
        add t1, zero, a1	# put base in t1 for computations
        addi t2, a2, -1		# t1 starts as the base, only need power - 1
        
        bge t0, t2, powExit	# skip loop if condition initially false
        powLoop:
            mul t1, t1, a1		# perform actual multiplication
            addi t0, t0, 1		# increment loop variable
            blt t0, t2, powLoop	# loop for t0 < t2
        
        powExit:
            add a0, zero, t1	# save result to return
            
            lw t2, 0(sp)	# restore t2
            lw t1, 4(sp)	# restore t1
            lw t0, 8(sp)	# restore t0
            addi sp, sp, 12	# readjust stack
            
            jalr zero, ra, 0
    
    # Arguments
    #	a1: ASCII code
    # Return values
    #	a0: translated number or negative if error
    .globl translateFromASCII
    translateFromASCII:
        addi sp, sp, -28	# adjust stack for 7 items
        sw t0, 24(sp)		# save t0
        sw t1, 20(sp)		# save t1
        sw t2, 16(sp)		# save t2
        sw t3, 12(sp)		# save t3
        sw t4, 8(sp)		# save t4
        sw t5, 4(sp)		# save t5
        sw t6, 0(sp)		# save t6
        
        addi t1, zero, 48	# '0'
        addi t2, zero, 57	# '9'
        addi t3, zero, 65	# 'A'
        addi t4, zero, 90	# 'Z'
        addi t5, zero, 97	# 'a'
        addi t6, zero, 122	# 'z'
        
        # ['0', '9']
        translateFromASCIICase1:
            blt a1, t1, translateFromASCIICase2	# char < '0'
            addi t0, t2, 1	# avoid using pseudoinstruction bgt
            bge a1, t0, translateFromASCIICase2	# char > '9'
            
            sub t0, a1, t1	# char - '0'
            
            jal zero, translateFromASCIICleanExit
        
        # ['A', 'Z']
        translateFromASCIICase2:
            blt a1, t3, translateFromASCIICase3	# char < 'A'
            addi t0, t4, 1	# avoid using pseudoinstruction bgt
            bge a1, t0, translateFromASCIICase3	# char > 'Z'
        
            sub t0, a1, t3	# char - 'A'
            addi t0, t0, 10	# add 10 to get number
            
            jal zero, translateFromASCIICleanExit
        
        # ['a', 'z']
        translateFromASCIICase3:
            blt a1, t5, translateFromASCIIErrorExit	# char < 'a'
            addi t0, t6, 1	# avoid using pseudoinstruction bgt
            bge a1, t0, translateFromASCIIErrorExit	# char > 'z'
        
            sub t0, a1, t5	# char - 'a'
            addi t0, t0, 10	# add 10 to get number
            
            jal zero, translateFromASCIICleanExit
        
        translateFromASCIIErrorExit:
            addi t0, zero, -1	# -1 indicates error occurred
        
        translateFromASCIICleanExit:
            add a0, zero, t0	# save result for return
            
            lw t6, 0(sp)	# restore t6
            lw t5, 4(sp)	# restore t5
            lw t4, 8(sp)	# restore t4
            lw t3, 12(sp)	# resotre t3
            lw t2, 16(sp)	# restore t2
            lw t1, 20(sp)	# restore t1
            lw t0, 24(sp)	# restore t0
            addi sp, sp, 28	# readjust stack
            
            jalr zero, ra, 0
    