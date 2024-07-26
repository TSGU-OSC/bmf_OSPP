/*
 * Copyright 2023 Babit Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "builder.hpp"
#include "nlohmann/json.hpp"

void task(){
    int scheduler_cnt = 0;
    auto graph = bmf::builder::Graph(bmf::builder::NormalMode);

    nlohmann::json decode_para = {
        {"input_path", "../../files/big_bunny_10s_30fps.mp4"}};
    auto video = graph.Decode(bmf_sdk::JsonParam(decode_para),"" , scheduler_cnt++);

    auto video_copied =
        graph.Module({video["video"]}, "copy_module", bmf::builder::CPP,
                        bmf_sdk::JsonParam(), "CopyModule",
                        "./libcopy_module.so", "copy_module:CopyModule",
                        bmf::builder::Immediate, scheduler_cnt++);


    nlohmann::json encode_para = {
        {"output_path", "./rgb2video.mp4"},
    };

    graph.Encode(video_copied,
                 bmf_sdk::JsonParam(encode_para),
                 "", scheduler_cnt++);

    nlohmann::json graph_para = {{"dump_graph", 1},
                                 {"scheduler_count", scheduler_cnt}};
    graph.SetOption(bmf_sdk::JsonParam(graph_para));
    graph.Run();
}

int main() {
    task();
}
