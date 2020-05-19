
from pymongo import MongoClient
import pymongo.errors as mongoerr
from datetime import datetime

user_doc1 = {
    "username": "Mary", "firstname": "Mike", "surname": "Doe", "dateofbirth": datetime(1977, 3, 22),
    "email": "maymike78@example.com", "score": 50}
user_doc2 = {
    "username": "Mary", "firstname": "Mike", "surname": "Doe", "dateofbirth": datetime(1977, 3, 22),
    "email": "maymike78@example.com", "score": 80}
user_docs = [
    {"username": "janedoe", "firstname": "Jane", "surname": "Doe", "dateofbirth": datetime(1974, 1, 12),
        "email": "janedoe74@example.com", "score": 70},
    {"username": "Woo", "firstname": "Mary", "surname": "Doe", "dateofbirth": datetime(1998, 4, 12),
        "email": "woomary98@example.com", "score": 80},
    {"username": "lee", "firstname": "Jane", "surname": "Doe", "dateofbirth": datetime(1989, 2, 1),
        "email": "janelee89@example.com", "score": 90}]


def clear_all():
    # delete all rows
    print(collection.delete_many({}))


def insert_dict():
    # insert rows
    print(collection.insert_one(user_doc1, bypass_document_validation=True))
    print(collection.insert_many(user_docs))


def update_Mary():
    #query and update
    print('all rows:', collection.count({}))
    print('match username = janedoe rows:',
          collection.count({"username": "janedoe"}))
    print('Mary data before update:',
          collection.find_one({"username": "Mary"}))
    collection.find_one_and_replace({"username": "May"}, user_doc2)
    print('Mary data after update:', collection.find_one({"username": "Mary"}))
    # update insert
    result = collection.update_one({'username':  "Mary"}, {
        '$set': user_doc2}, upsert=True)
    print('Mary data after insert update rows:', result.matched_count)


def find_jane():
    # 大于条件
    print('match firstname = Jane and score >80 rows:',
          collection.count({"firstname": "Jane", 'score': {"$gt": 80}}))

    # top(n)，结果排序，限定记录数，限定显示字段
    for post in collection.find({'firstname': 'Jane'}, {"firstname": 1, "email": 2, "score": 3}, sort=[("score", -1)]).limit(2).skip(1):
        print('find 2nd row', post)
    # or的条件
    for post in collection.find({'$or': [{'firstname': 'Jane'}, {'firstname': 'Mary'}]}, {"firstname": 1, "email": 2, "score": 3}):
        print('or select ', post)
    # 正则表达式
    for post in collection.find({"firstname": {'$regex': '^M'}}, {"firstname": 1, "email": 2, "score": 3}):
        print('reg start with J', post)
    
def find_mary_viaIndex():
    # Create index on username property called "username_idx"
    collection.create_index("firstname", name="firstname_idx")
    print('find Mary:',collection.find_one({"firstname" : "Mary"},{"firstname":1,"email":2,"score":3}))
    #Delete index called "username_idx"
    collection.drop_index("firstname_idx")    

def export_csv():
    import csv
    FIELDS = [ 'firstname','email','_id']
    csv_file = open('test.csv', 'w')  
    dict_writer = csv.DictWriter(csv_file, fieldnames=FIELDS)  
    dict_writer.writeheader()
    dict_writer.writerows(collection.find({},{"firstname":1,"email":2})) 


def del_Mary():
    # delete all rows
    print('Mary data delete:', collection.delete_one({"username": "Mary"}))


if __name__ == "__main__":
    try:
        client = MongoClient('172.17.0.11:27017', connect=True)
        db = client['learn']
        collection = db['users']
        clear_all()
        insert_dict()
        update_Mary()
        find_jane()
        find_mary_viaIndex()
        export_csv()
        del_Mary()
    except mongoerr.ConnectionFailure as e:
        print("Could not connect: %s" % e)
    finally:
        client.close()
