#ifndef __BLOCK_H__
#define __BLOCK_H__

enum BlockType {
    BlockType_Default = 0,
    BlockType_Grass,
    BlockType_Dirt,
    BlockType_Water,
    BlockType_Stone,
    BlockType_Wood,
    BlockType_Sand,
    BlockType_NumTypes,
    BlockType_Ice,
    BlockType_Snow,
};


class Block {
public:
    Block();
    Block(bool active, BlockType blockType);
    ~Block();
    bool isActive();
    void setActive(bool status);
    void setBlockType(BlockType type);
    BlockType getBlockType();
private:
    bool active;
    BlockType blockType;
};
#endif // __BLOCK_H__