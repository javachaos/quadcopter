/**
 * Communicator.cpp
 *
 * Communicator agent to relay messages via the Blackboard agent.
 *
 *  Created on: Mar 16, 2016
 *      Author: fred
 */
#include "Communicator.h"

using namespace std;
namespace Quadcopter {

void Communicator::init(shared_ptr<Blackboard> bb) {
	bb->addMessage(ID_LOG,ID_COMM,"COMMUNICATOR: Initializing Listener.");
	cinit();
	bb->addMessage(ID_LOG,ID_COMM,"COMMUNICATOR: Initialized.");
}

void Communicator::update(shared_ptr<Blackboard> bb) {
	Blackboard::BBMessage m = bb->checkForMessage(this->getId());
	if(m.to == ID_COMM) {
            Data d;
            d.to = (unsigned char) m.to;
            d.from = (unsigned char) m.from;
            d.timestamp = m.timestamp;
            const char* payload = m.msg.c_str();
            memcpy(&d.payload, payload, MAX_DATA_SIZE);
	    const Data reply = cupdate(d);
            addReply(reply,bb);
        } else {//Querry client for data.
	    Data tmp = {MAX_MSG_SIZE,0,0,bb->getTimestamp(),"GET"};
	    const Data reply = cupdate(tmp);
            addReply(reply, bb);
        }
}

bool Communicator::validateData(const Data reply) {
    if(reply.to > NUM_DEVICES || reply.from > NUM_DEVICES
    || reply.to < 0 || reply.from < 0) {
        return false;
    } else {
        if(reply.timestamp <= 0) {
            return false;
        } else {
            if(string(reply.payload).empty()) {
                return false;
            } else {
                return parse(reply.payload);
            }
        }
    }
}

void Communicator::addReply(const Data reply, shared_ptr<Blackboard> bb) {
    if (validateData(reply)) {
        int to = reply.to;
        int from = reply.from;
        unsigned long timestamp = reply.timestamp;
        string msg = string(reply.payload);
        bb->addMessage(to, from, timestamp, msg);
    }
}

// // Level is between 0 (no compression), 9 (slow compression, small output).
// string Communicator::compressWithLzma(const std::string& in, int level) {
//   std::string result;
//   result.resize(in.size() + (in.size() >> 2) + 128);
//   size_t out_pos = 0;
//   if (LZMA_OK != lzma_easy_buffer_encode(
//       level, LZMA_CHECK_CRC32, NULL,
//       reinterpret_cast<uint8_t*>(const_cast<char*>(in.data())), in.size(),
//       reinterpret_cast<uint8_t*>(&result[0]), &out_pos, result.size()))
//     abort();
//   result.resize(out_pos);
//   return result;
// }

// string Communicator::decompressWithLzma(const std::string& in) {
//   static const size_t kMemLimit = 1 << 30;  // 1 GB.
//   lzma_stream strm = LZMA_STREAM_INIT;
//   std::string result;
//   result.resize(8192);
//   size_t result_used = 0;
//   lzma_ret ret;
//   ret = lzma_stream_decoder(&strm, kMemLimit, LZMA_CONCATENATED);
//   if (ret != LZMA_OK)
//     abort();
//   size_t avail0 = result.size();
//   strm.next_in = reinterpret_cast<const uint8_t*>(in.data());
//   strm.avail_in = in.size();
//   strm.next_out = reinterpret_cast<uint8_t*>(&result[0]);
//   strm.avail_out = avail0;
//   while (true) {
//     ret = lzma_code(&strm, strm.avail_in == 0 ? LZMA_FINISH : LZMA_RUN);
//     if (ret == LZMA_STREAM_END) {
//       result_used += avail0 - strm.avail_out;
//       if (0 != strm.avail_in)  // Guaranteed by lzma_stream_decoder().
//         abort();
//       result.resize(result_used);
//       lzma_end(&strm);
//       return result;
//     }
//     if (ret != LZMA_OK)
//       abort();
//     if (strm.avail_out == 0) {
//       result_used += avail0 - strm.avail_out;
//       result.resize(result.size() << 1);
//       strm.next_out = reinterpret_cast<uint8_t*>(&result[0] + result_used);
//       strm.avail_out = avail0 = result.size() - result_used;
//     }
//   }
// }

Communicator::~Communicator() {
	cclose();
}

}
