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

#include "../include/output_stream.h"

#include <bmf/sdk/log.h>

BEGIN_BMF_ENGINE_NS
USE_BMF_SDK_NS

MirrorStream::MirrorStream(
    std::shared_ptr<InputStreamManager> input_stream_manager, int stream_id)
    : input_stream_manager_(input_stream_manager), stream_id_(stream_id) {}

OutputStream::OutputStream(int stream_id, std::string const &identifier,
                           std::string const &alias, std::string const &notify)
    : stream_id_(stream_id), identifier_(identifier), alias_(alias),
      notify_(notify), queue_(std::make_shared<SafeQueue<Packet>>()) {
        queue_->set_identifier(identifier_);
      }

int OutputStream::add_mirror_stream(
    std::shared_ptr<InputStreamManager> input_stream_manager, int stream_id) {
    mirror_streams_.emplace_back(MirrorStream(input_stream_manager, stream_id));
    return 0;
}

int OutputStream::propagate_packets(
    std::shared_ptr<SafeQueue<Packet>> packets) {
    static int cnt = 0;
    /* Do not Split */
    // while (!queue_->empty()) {
    //     Packet pkt;
    //     if(queue_->pop(pkt)) {
    //         for (auto &s : mirror_streams_) {
    //             auto copy_queue = std::make_shared<SafeQueue<Packet>>();
    //             copy_queue->push(pkt);
    //             copy_queue->set_identifier(identifier_);
    //             s.input_stream_manager_->add_packets(s.stream_id_, copy_queue);
    //             std::cout << ++cnt << std::endl;
    //         }
    //     }
    // }
    /* Data Splitting(Debuging) */
    while (!queue_->empty()) {
        Packet pkt;
        if (queue_->pop(pkt)) {
            static size_t stream_index = 0; // To keep track of the current stream in mirror_streams_

            auto &s = mirror_streams_[stream_index];
            auto copy_queue = std::make_shared<SafeQueue<Packet>>();
            copy_queue->push(pkt);
            copy_queue->set_identifier(identifier_);
            BMFLOG(BMF_INFO) << "Stream_index: " << stream_index 
                             << "\tmirror_streams' size: " << mirror_streams_.size()
                             << "\tCount :" << ++cnt;
            /* original code for single node push pkts to input stream */
            s.input_stream_manager_->add_packets(s.stream_id_, copy_queue);
            /* code for multi node output(do not use it for now) */
            // s.input_stream_manager_->add_packets(s.stream_id_, copy_queue, node_id_);
            
            // std::cout << ++cnt << std::endl;
            stream_index = (stream_index + 1) % mirror_streams_.size();
        }
    }

    /* original version */
    // for (auto &s : mirror_streams_) {
    //     auto copy_queue = std::make_shared<SafeQueue<Packet>>(*packets.get());
    //     copy_queue->set_identifier(identifier_);
    //     s.input_stream_manager_->add_packets(s.stream_id_, copy_queue);
    //     std::cout << ++cnt << std::endl;
    // }
    return 0;
}
int OutputStream::add_upstream_nodes(int node_id) {
    /* TODO: the node_id_ need to be placed right class like OuputStreamManager */
    node_id_ = node_id;
    for (auto &s : mirror_streams_) {
        s.input_stream_manager_->add_upstream_nodes(node_id);
    }
    return 0;
}

int OutputStream::add_packets(std::shared_ptr<SafeQueue<Packet>> packets){
    Packet pkt;
    while (packets->pop(pkt)) {
        queue_->push(pkt);
        std::cout << "output stream's address:" << this << "\tqueue's address:" << &queue_ << "\tpkt timestamp: " << pkt.timestamp() << std::endl;
        // advance time bounding
        // next_time_bounding_ = pkt.timestamp() + 1;
        // if received EOS, set stream done
        // here we can't use pkt.get_timestamp() + 1 since
        // Timestamp.DONE = Timestamp.EOS + 2
        if (pkt.timestamp() == EOS or pkt.timestamp() == BMF_EOF) {
            /* add EOF pkt for multi downstream node */
            for (size_t i = 1; i < mirror_streams_.size(); i++) {
                queue_->push(Packet::generate_eof_packet());
            }
            // next_time_bounding_ = DONE;
            // BMFLOG_NODE(BMF_INFO, node_id_) << "eof received";
            // add node to scheduler thread until this EOS is processed
            // graph_output_stream may not have attribute node
            // if (node_id_ >= 0) {
            //    throttled_cb_(node_id_, true);
            //}
        }
        // wake up event
        // fill_packet_event_.notify_all();
    }
    return 0;
}
END_BMF_ENGINE_NS
