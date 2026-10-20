#include "check.h"
#include "scale/units.h"

int main()
{
    // 453.592 g == 1 lb == 1000 milli-lb
    CHECK_EQ(gramsToMilliLb(454), 1001);
    CHECK_EQ(gramsToMilliLb(12), 26);      // 12 g cup ~= 0.026 lb
    CHECK_EQ(milliLbToGrams(1000), 454);

    // legacy API still behaves as the firmware expects
    CHECK_EQ(ConvertWeight(10, UNIT_LB, UNIT_OZ), 160);
    CHECK_EQ(ConvertWeight(5, UNIT_LB, UNIT_LB), 5);

    TEST_MAIN_END();
}
