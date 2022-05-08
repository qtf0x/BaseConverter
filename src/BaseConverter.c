/**
 * @file BaseConverter.c
 * @author Vincent Marias (@vincent-marias)
 * @date 2022-05-08
 *
 * @brief A number base converter (base [2, 36] -> base 10).
 */

#include <inttypes.h>
#include <stdio.h>

#define VALUE_MAX 41 * sizeof(uint8_t)

const uint32_t zero = 0;
uint32_t ra, sp, gp, tp, fp;
uint32_t t0, t1, t2, t3, t4, t5, t6;
uint32_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
uint32_t a0, a1, a2, a3, a4, a5, a6, a7;

uint8_t* pa1;

uint8_t value[VALUE_MAX];

uint8_t basePrompt[] =
    "Please enter the base of the number you are using (0 to exit): ";
uint8_t valuePrompt[] = "Please enter the value: ";
uint8_t resultPrompt[] = "The given value in base 10 is: ";
uint8_t badValPrompt[] = "The value entered is not valid for the base entered";

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

    a1 = 69420;
    printResult();

    pa1 = &value;
    printf("Length of input: %" SCNd32 "\n", a0);

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

/**
 * input:
 *      a1 - value after translation
 * output:
 *      none
 */
void printResult() { printf("%s%" SCNd32 "\n", resultPrompt, a1); }

void translateValue() {}

/**
 * input:
 *      a1 - the address of a string
 * output:
 *      a0 - the length of the string
 */
void strlen() {
    uint32_t savet0 = t0;
    uint32_t savet1 = t1;

    t0 = 0;
    t1 = '\0';

    while (t0 < VALUE_MAX / sizeof(uint8_t)) {
        if (*(pa1 + t0 * sizeof(uint8_t)) == t1) {
            break;
        }
    }

    a0 = t0;

    t0 = savet0;
    t1 = savet1;
}
