#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

#include<QDebug>
#include<stdio.h>

namespace BlockType {
enum type{NORMAL, BONUS, DEATH};
}

// node
struct BlockData
{
    int x, y; // coor of block
    int width, height; // shape of block
    BlockType::type type;
    BlockData * next;
};

// linked list
class Block_Data
{
public:
    Block_Data();
    ~Block_Data();
    void init(BlockData **d, int x=0,int y=0, int width=0,int height=0, BlockType::type type__ = BlockType::NORMAL);
    void insert(BlockData *d);
    void updata(int speed);

    BlockData* remove(int x);
    BlockData* remove(int x,int y);
    bool judge(int y);
    void clear();

    BlockData * get_pos(){ return head; }
    void show();

private:
    BlockData * head;
    BlockData * tail;
};

#endif // BLOCK_DATA_H
