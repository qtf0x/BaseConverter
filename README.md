### CSCI 341 - Computer Organization (Spring 2022)

# Number Base Converter

1. Include YOUR NAME.

   Vincent Marias

<br>

2. Any additional pseudocode (in C) for your implementation.

   See `src/BaseConverter.c`

<br>

3. Describe the challenges you encountered and how you surmounted them.

- At first I figured that this assignment was so straightforward that I would just jump right into the assembly. That was a mistake, and I soon realized that it was going to take way longer than I wanted it to. So I did what I've done for all the other assignments in this class, and made a full working version of the program in C. I used global variables named after the RISC-V registers to make translating to assembly easier.

- One of the hardest things in this assignment was making sure all of the loops and if-else statements were translated correctly from my C code to assembly instructions. I had to be careful that the logic was actually the same between the two, and not to use pseudoinstructions.

- For quite a while, I had my assembly procedures written and I thought they worked. But I was getting weird errors, and it was because those procedures modified the temp variables in without using the stack to save and restore them. I had to fix this in all my procdures that had this problem.

<br>

4. What did you like about the assignment?

- I'm thankful that you outlined a set of procedures for me to break the program into. This saved me a lot of time when it came to writing the code.

- It's also nice that you provided a lot a public test cases that cover pretty much every edge case. This way, I'm sure that my program completely passes a lot of test cases before I turn in the assignment, and they also revealed a few bugs I would not have caught otherwise.

<br>

5. How long did you spend working on this assignment?

   ~10 hours
