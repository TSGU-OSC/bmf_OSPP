/**
 * Copyright by 2024 Jack Lau
 * 
 */

#ifndef BMF_SPLIT_MODULE_H
#define BMF_SPLIT_MODULE_H

#include <bmf/sdk/bmf.h>
#include <bmf/sdk/packet.h>

USE_BMF_SDK_NS

class SplitModule : public Module {
  public:
    SplitModule(int node_id, JsonParam option) : Module(node_id, option) {}

    ~SplitModule() {}

    virtual int process(Task &task);
};

#endif