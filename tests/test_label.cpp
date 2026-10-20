#include "check.h"
#include "scale/label.h"

int main()
{
    char line[LABEL_LINE_LEN];

    CHECK_EQ(formatLabelLine(4011, 125, line), 0);
    CHECK_STR(line, "BANANAS  $1.25");

    // 20 lb is within the 30 lb capacity
    CHECK_EQ(checkCapacity(20000), 0);

    TEST_MAIN_END();
}
