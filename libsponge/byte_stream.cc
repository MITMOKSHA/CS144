#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : buffer_(std::move(deque<char>(0))), capacity_(capacity), end_write_(false),
                    read_num_(0), write_num_(0) { DUMMY_CODE(capacity); }

size_t ByteStream::write(const string &data) {
    DUMMY_CODE(data);
    size_t can_write = min(data.size(), remaining_capacity());
    for (size_t i = 0; i < can_write; ++i) {
        buffer_.push_back(data[i]);    // push from the input side.
    }
    write_num_ += can_write;
    return can_write;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    DUMMY_CODE(len);
    size_t can_peek = min(len, buffer_.size());
    string peek_data = "";
    for (size_t i = 0; i < can_peek; ++i) {
        peek_data += buffer_[i];
    }
    return peek_data;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    DUMMY_CODE(len);
    if (len > buffer_.size()) {
        set_error();
        return;
    }
    for (size_t i = 0; i < len; ++i) {
        buffer_.pop_front();           // removed from the output side.
    }
    read_num_ += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    DUMMY_CODE(len);
    string message = "";
    size_t can_read = min(len, buffer_.size());  // next "len" bytes.
    for (size_t i = 0; i < can_read; ++i) {
        message += buffer_.front();
        buffer_.pop_front();
    }
    read_num_ += can_read;
    return message;
}

void ByteStream::end_input() { end_write_ = true; }

bool ByteStream::input_ended() const { return end_write_; }

size_t ByteStream::buffer_size() const { return buffer_.size(); }

bool ByteStream::buffer_empty() const { return buffer_.empty(); }

bool ByteStream::eof() const { return buffer_empty() && end_write_; }

size_t ByteStream::bytes_written() const { return write_num_; }

size_t ByteStream::bytes_read() const { return read_num_; }

size_t ByteStream::remaining_capacity() const { return capacity_ - buffer_.size(); }
