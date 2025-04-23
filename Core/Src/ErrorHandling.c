/*
 * ErrorHandling.c
 *
 *  Created on: Apr 3, 2025
 *      Author: tylerschmitz
 */

#include "ErrorHandling.h"

void APPLICATION_ASSERT(bool bVal){
	if (!bVal){
		while (1){};
	}
}


