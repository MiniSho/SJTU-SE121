#define LEFT 0
#define RIGHT 1
struct branch typedef Branch;

class red_black_tree {
    Branch* root;
    int size;

   public:
    red_black_tree();
    void add(int value);
    void get(int value);
    void print(Branch* node);
    void print();
    int getRedNum();

   private:
    Branch* grandfather(Branch* node);
    Branch* uncle(Branch* node);
    void balancing(Branch* node);
    void rotate(Branch* node, bool direction);
};
// namespace tpa