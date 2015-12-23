#ifndef DataTypes_H
#define DataTypes_H

#include <stdint.h>

#define u08 uint8_t

typedef enum
{
  PIN_LOW  = 0,
  PIN_HIGH = 1
} PinState;

typedef enum
{
  FALSE = 0,
  TRUE  = 1
} BOOL;

#ifdef CPPUTEST
//CppUTest framework has ambiguous overloads if we mark RegisterPointers as volatile
typedef uint8_t * RegisterPointer;
#else
typedef volatile uint8_t * RegisterPointer;
#endif

#ifndef NULL
#define NULL 0
#endif

#define RETURN_IF_NULL(pointer) if ((pointer) == NULL) return
#define RETURN_VALUE_IF_NULL(pointer, retVal) if ((pointer) == NULL) return (retVal)

#endif
