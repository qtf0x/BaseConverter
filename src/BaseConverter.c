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
uint8_t errorPrompt[] = "The value entered is not valid for the base entered";

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
void translateValue();

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
    while (1) {
        getBase();

        if (a0 == 0) {
            return 0;
        }

        s0 = a0; // base

        getValue();

        a2 = s0;
        translateValue();

        if (a1) {
            printf("%s\n\n", errorPrompt);
        } else {
            a1 = a0;
            printResult();
        }
    }
}

/**
 * input:
 *      none
 * output:
 *      a0 - base chosen
 */
void getBase() {
    uint32_t savet0 = t0;
    uint32_t savet1 = t1;
    uint32_t savet2 = t2;

    t0 = -1;
    t1 = 2;
    t2 = 36;

    while (t0 != 0 && (t0 < t1 || t0 > t2)) {
        printf("%s", basePrompt);
        scanf("%" SCNd32, &t0);
    }

    a0 = t0;

    t0 = savet0;
    t1 = savet1;
    t2 = savet2;
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
void printResult() { printf("%s%" SCNd32 "\n\n", resultPrompt, a1); }

/**
 * input:
 *      a2 - base to convert from
 * output:
 *      a0 - translated value
 *      a1 - error flag (1 for error)
 */
void translateValue() {
    t0 = 1;   // loop var
    t1 = '-'; // 45
    t2 = 0;   // result

    pa1 = &value;
    strlen();
    s3 = a0; // characters to check
    t4 = a0;

    while (t0 <= s3) {
        t4 = s3 - t0;
        t5 = value[t4]; // char to translate

        // if negative sign in front
        if (t5 == t1 && t4 == 0) {
            t2 *= -1;
            break;
        }

        a1 = t5;
        translateFromASCII();
        t3 = a0; // translated value

        if (t3 < 0 || t3 >= a2) {
            a1 = 1;
            return;
        }

        t6 = a2;     // save a2
        a1 = a2;     // base
        a2 = t0 - 1; // power
        pow();
        a2 = t6; // restore a2

        t6 = t3 * a0;
        t2 += t6;

        ++t0;
    }

    a0 = t2;
    a1 = 0;
}

/**
 * input:
 *      pa1 - the address of a string
 * output:
 *      a0 - the length of the string
 */
void strlen() {
    uint32_t savet0 = t0;
    uint32_t savet1 = t1;
    uint32_t savet2 = t2;
    uint32_t savet3 = t3;

    t0 = 0;
    t1 = '\0';
    t2 = VALUE_MAX / sizeof(uint8_t);

    while (t0 < t2) {
        t3 = t0 * sizeof(uint8_t);
        if (*(pa1 + t3) == t1) {
            break;
        }

        ++t0;
    }

    a0 = t0;

    t0 = savet0;
    t1 = savet1;
    t2 = savet2;
    t3 = savet3;
}

/**
 * input:
 *      a1 - base
 *      a2 - power
 * output:
 *      a0 - result
 */
void pow() {
    uint32_t savet0 = t0;
    uint32_t savet1 = t1;
    uint32_t savet2 = t2;

    if (a2 <= 0) {
        t1 = 1;
    } else {
        t0 = 0;
        t1 = a1;
        t2 = a2 - 1;

        while (t0 < t2) {
            t1 *= a1;

            ++t0;
        }
    }

    a0 = t1;

    t0 = savet0;
    t1 = savet1;
    t2 = savet2;
}

/**
 * input:
 *      a1 - ASCII code
 * output:
 *      a0 - translated number or negative if error
 */
void translateFromASCII() {
    uint32_t savet0 = t0;
    uint32_t savet1 = t1;
    uint32_t savet2 = t2;
    uint32_t savet3 = t3;
    uint32_t savet4 = t4;
    uint32_t savet5 = t5;
    uint32_t savet6 = t6;

    t1 = 48;
    t2 = 57;
    t3 = 65;
    t4 = 90;
    t5 = 97;
    t6 = 122;

    if (a1 >= t1 && a1 <= t2) {
        t0 = a1 - t1;
    } else if (a1 >= t3 && a1 <= t4) {
        t0 = a1 - t3 + 10;
    } else if (a1 >= t5 && a1 <= t6) {
        t0 = a1 - t5 + 10;
    } else {
        t0 = -1;
    }

    a0 = t0;

    t0 = savet0;
    t1 = savet1;
    t2 = savet2;
    t3 = savet3;
    t4 = savet4;
    t5 = savet5;
    t6 = savet6;
}
