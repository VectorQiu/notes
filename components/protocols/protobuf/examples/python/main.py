import addressbook_pb2

# 创建一个 Person 对象
person = addressbook_pb2.Person()
person.name = "John Doe"
person.id = 1234
person.email = "johndoe@example.com"

# 将 Person 对象添加到 AddressBook
address_book = addressbook_pb2.AddressBook()
address_book.people.append(person)

# 序列化到二进制格式
with open("addressbook.bin", "wb") as f:
    f.write(address_book.SerializeToString())

# 从二进制文件反序列化
address_book_read = addressbook_pb2.AddressBook()
with open("addressbook.bin", "rb") as f:
    address_book_read.ParseFromString(f.read())

# 打印读取的数据
for person in address_book_read.people:
    print(f"Name: {person.name}, ID: {person.id}, Email: {person.email}")
