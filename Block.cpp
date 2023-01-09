#include "Block.h"

Block::Block()
{
    active = false;
    blockType = BlockType::BlockType_Default;
}

Block::Block(bool act, BlockType type)
{
    active = act;
    blockType = type;
}

Block::~Block()
{

}

bool Block::isActive()
{
    return active;
}

void Block::setActive(bool status)
{
    active = status;
}

void Block::setBlockType(BlockType type)
{
    blockType = type;
}

BlockType Block::getBlockType(){
    return blockType;
}