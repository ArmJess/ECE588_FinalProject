#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 0

#ifndef SIGNAL_H
#define SIGNAL_H

/*MSI and MESI Signals:
P_WR: Processor Write
P_RD: Processor Read
B_WR: Bus Write
B_RD: Bus Read

Additional MESI Signals:
P_Writeback:= Processor Write Back to Memory

MSI Diagram directions:
I (P_WR) -> M
I (P_RD) -> S
M (P_RD or P_WR) -> M
M (B_WR) -> I
M (B_RD) -> S
S (P_RD) -> S
S (P_WR) -> M
S (B_RD) -> S
S (B_WR) -> I

MESI Diagram directions:
I (P_WR) -> M
I (P_RD) -> S
I (P_RD) -> E
M (P_RD or P_WR) -> M
M (P_Writeback or B_WR) -> I
M (B_RD) -> S
S (P_RD) -> S
S (P_WR) -> M
S (B_WR) -> I
S (B_RD) -> S
E (P_RD) -> E
E (P_WR) -> M
E (B_WR) -> I
E (B_RD) -> S*/


