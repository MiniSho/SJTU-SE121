#define LEFT 0
#define RIGHT 1
struct branch typedef Branch;

class red_black_tree {
    Branch* root;
    int size;
    int count_balances;
    int doubleRedBalancing;
    int height(Branch* ptr);
    int blackheight(Branch* ptr);

   public:
    red_black_tree();
    void add(int value);
    void get(int value);
    void print(Branch* node);
    void print();
    int getRedNum();
    int getHeight() { return height(root); }
    int getBlackHeight() { return blackheight(root); }
    int getCount() { return count_balances; }
    void clear() { count_balances = 0; }

   private:
    Branch* grandfather(Branch* node);
    Branch* uncle(Branch* node);
    bool balancing(Branch* node);
    void rotate(Branch* node, bool direction);
};
// namespace tpa