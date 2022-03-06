#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include "signal.h"

//MESI protocol
status_t mesi(struct per_core_stats currentStats, int processor_num);

//MSI protocol
status_t msi (struct per_core_stats currentStats, int processor_num);
