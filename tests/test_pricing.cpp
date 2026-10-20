#include "check.h"
#include "scale/plu.h"
#include "scale/pricing.h"

int main()
{
    // 1.500 lb gross, 0.020 lb tare -> 1.480 lb net
    CHECK_EQ(netWeightMilliLb(1500, 20), 1480);
    // invalid inputs
    CHECK_EQ(netWeightMilliLb(0, 0), -1);
    CHECK_EQ(netWeightMilliLb(100, 100), -1);

    // 1.480 lb * $9.99 = $14.7852 -> 1479 cents
    CHECK_EQ(itemPriceCents(2001, 1500, 20), 1479);
    // unknown PLU
    CHECK_EQ(itemPriceCents(9999, 1000, 0), -1);

    CHECK_EQ(findPlu(4011) != nullptr, 1);
    CHECK_EQ(findPlu(1234) == nullptr, 1);

    TEST_MAIN_END();
}
