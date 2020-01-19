#!/usr/bin/env python3


def testFormat():

    #printf type 占位符--- obsolete
    print("Suzhou is %d years old. %s lives in here." % (2500, "alex"))

    #https://docs.python.org/3/library/string.html#formatstrings
    x = 3
    print('{:4d} {:4d} {:4d}'.format(x, x*x, x*x*x))
    x = 4
    print('{:4x} {:4x} {:4x}'.format(x, x*x, x*x*x))
    x = 5.0
    print('{:4.1f} {:4.1f} {:4.1f}'.format(x, x*x, x*x*x))
    import math
    print('The value of PI is approximately {}.'.format(math.pi))
    print('The value of PI is approximately {!s}.'.format(math.pi))
    print('The value of PI is approximately {:4.2f}.'.format(math.pi))
    for name, phone in {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}.items():
        print('{1:5}=>{0:6}'.format(name, phone))

    print('This {food} is {adjective}.'.format(
        food='spam', adjective='absolutely horrible'))
    print('The story of {1}, {0}, and {other}.'.format(
        'Bill', 'Manfred', other='Georg'))

    person = {"name": "hoxis", "age": 18}
    print('hello, {name}. you are {age}?'.format(**person))

    # https://docs.python.org/3/reference/lexical_analysis.html#f-strings
    print(f"hi, {person['name']}, are you {person['age']}")
    print(f"hi, {person['name'].upper()}, are you {2+3+4}")
    x = 3
    print(f'{x:4} {x**2:4} {x**3:4}')
    x = 4.0
    print(f'{x:4.1f} {x**2:4.1f} {x**3:4.1f}')
    metro_areas = [
        ('Tokyo', 'JP', 36.933, (35.689722, 139.691667)),   # <1>
        ('Delhi NCR', 'IN', 21.935, (28.613889, 77.208889)),
        ('Mexico City', 'MX', 20.142, (19.433333, -99.133333)),
        ('New York-Newark', 'US', 20.104, (40.808611, -74.020386)),
        ('Sao Paulo', 'BR', 19.649, (-23.547778, -46.635833)),
    ]
    print('----------metro_areas--------')
    print(f"{'':15} | {'lat.':^9} | {'long.':^9}")
    for name, _,_, (latitude, longitude) in metro_areas:  # <2>
        if longitude <= 0:  # <3>
            print(f'{name:^15} | {latitude:<9.4f} | {longitude:>9.4f}')


if __name__ == "__main__":
    testFormat()
