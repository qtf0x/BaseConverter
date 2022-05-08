/**
 * @file BaseConverter.c
 * @author Vincent Marias (@vincent-marias)
 * @date 2022-05-08
 *
 * @brief A number base converter (base [2, 36] -> base 10).
 */

#include <inttypes.h>
#include <stdio.h>

#define VALUE_MAX 10 * sizeof(uint32_t)

const uint32_t zero = 0;
uint32_t ra, sp, gp, tp, fp;
uint32_t t0, t1, t2, t3, t4, t5, t6;
uint32_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
uint32_t a0, a1, a2, a3, a4, a5, a6, a7;

char value[VALUE_MAX];

char basePrompt[] =
    "Please enter the base of the number you are using (0 to exit): ";
char valuePrompt[] = "Please enter the value: ";
char resultPrompt[] = "The given value in base 10 is: ";
char badValPrompt[] = "The value entered is not valid for the base entered";

/**
 * @brief Gets the base from the user and returns it. Performs bounds checking
 * to ensure user input is valid.
 */
void getBase();

/**
 * @brief Gets the value from the user and saves it to memory.
 */
void getValue();

/**
 * @brief Prints the result after translation has been performed.
 */
void printResult();

/**
 * @brief Accepts the base as a parameter and translates the value in memory to
 * base 10. If an error does not occur in translation, return the value. If an
 * error does occur in translation, return an error flag.
 */
void translateResult();

/**
 * @brief Given the address of a string, return the length of the string.
 */
void strlen();

/**
 * @brief Given a number and the power returns the result of raising the number
 * to the power.
 */
void pow();

/**
 * @brief Given a character in ASCII code, attempt to translate it to a
 * numerical value. Returns a negative number if an error occurs.
 */
void translateFromASCII();

int main() {
    getBase();

    if (a0 == 0) {
        return 0;
    }

    getValue();

    return 0;
}

/**
 * input:
 *      none
 * output:
 *      a0 - base chosem
 */
void getBase() {
    uint32_t savet0 = t0;
    t0 = -1;

    while (t0 != 0 && (t0 < 2 || t0 > 36)) {
        printf("%s", basePrompt);
        scanf("%" SCNd32, &t0);
    }

    a0 = t0;
    t0 = savet0;
}

/**
 * input:
 *      none
 * output:
 *      none
 */
void getValue() {
    printf("%s", valuePrompt);
    scanf("%s", value);
}
