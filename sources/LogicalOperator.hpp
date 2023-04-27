
struct LogicalOperator
{virtual bool operator()(int lv, int rv) const = 0;};

struct Bigger:public LogicalOperator 
{bool operator()(int lv, int rv) const override {return lv > rv;}};

struct Equel:public LogicalOperator 
{bool operator()(int lv, int rv) const override {return lv == rv;}};
