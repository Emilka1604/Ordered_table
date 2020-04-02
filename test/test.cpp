#include "stack.h"
#include <gtest.h>

TEST(Unordered_table<polynom>, can_push_element) {
	Unordered_table<polynom> t;
	polynom p;
	p.parser("X^2");
	t.push(1, p);
	EXPECT_TRUE(t.getelem() == p);
}


