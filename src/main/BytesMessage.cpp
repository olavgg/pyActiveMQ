/*
  Copyright 2007 Albert Strasheim <fullung@gmail.com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <boost/python/class.hpp>
#include <boost/python/str.hpp>

#include <cms/BytesMessage.h>

#include <iostream>

namespace py = boost::python;

using cms::BytesMessage;
using cms::Message;

PyObject* BytesMessage_getBodyBytes(BytesMessage const& self)
{
    return py::incref(py::str(reinterpret_cast<const char*>(self.getBodyBytes()), self.getBodyLength()).ptr());
}

void BytesMessage_setBodyBytes(BytesMessage& This, const std::string& buffer)
{
    This.setBodyBytes(reinterpret_cast<const unsigned char*>(buffer.c_str()), buffer.length());
}

std::string BytesMessage_readBytes(BytesMessage& This)
{
    // TODO make this buffer size configurable
    std::vector<unsigned char> buffer(This.getBodyLength());
    std::size_t length = This.readBytes(buffer);
    return "";
}

void BytesMessage_writeBytes(BytesMessage& This, const std::string& buffer)
{
    std::vector<unsigned char> buffer2(buffer.size());
    for (std::size_t i = 0; i < buffer.size(); i++) {
        buffer2.push_back(buffer[i]);
    }
    This.writeBytes(buffer2);
}

void export_BytesMessage()
{
    py::class_<BytesMessage, py::bases<Message>, boost::noncopyable>("BytesMessage", py::no_init)
        .add_property("bodyBytes", BytesMessage_getBodyBytes, BytesMessage_setBodyBytes)
        .add_property("bodyLength", &BytesMessage::getBodyLength)
        .def("reset", &BytesMessage::reset)
        .def("readBoolean", &BytesMessage::readBoolean)
        .def("writeBoolean", &BytesMessage::writeBoolean)
        .def("readByte", &BytesMessage::readByte)
        .def("writeByte", &BytesMessage::writeByte)
        .def("readBytes", BytesMessage_readBytes)
        .def("writeBytes", BytesMessage_writeBytes)
        .def("readChar", &BytesMessage::readChar)
        .def("writeChar", &BytesMessage::writeChar)
        .def("readFloat", &BytesMessage::readFloat)
        .def("writeFloat", &BytesMessage::writeFloat)
        .def("readDouble", &BytesMessage::readDouble)
        .def("writeDouble", &BytesMessage::writeDouble)
        .def("readShort", &BytesMessage::readShort)
        .def("writeShort", &BytesMessage::writeShort)
        .def("readUnsignedShort", &BytesMessage::readUnsignedShort)
        .def("writeUnsignedShort", &BytesMessage::writeUnsignedShort)
        .def("readInt", &BytesMessage::readInt)
        .def("writeInt", &BytesMessage::writeInt)
        .def("readLong", &BytesMessage::readLong)
        .def("writeLong", &BytesMessage::writeLong)
        .def("readString", &BytesMessage::readString)
        .def("writeString", &BytesMessage::writeString)
        .def("readUTF", &BytesMessage::readUTF)
        .def("writeUTF", &BytesMessage::writeUTF)
        ;
}
