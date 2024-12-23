#ifndef SRC_ACAL_LAB_INCLUDES_MODELS_ALEXNET_ALEXNET_H_
#define SRC_ACAL_LAB_INCLUDES_MODELS_ALEXNET_ALEXNET_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info.h"
#include "acal_lab/includes/op.h"

namespace acal_lab {

void alexNet(convInfo*, gemmInfo*, mxPlInfo*, tensorInfo*, quantiInfo*);

}
#endif  // SRC_ACAL_LAB_INCLUDES_MODELS_ALEXNET_ALEXNET_H_
