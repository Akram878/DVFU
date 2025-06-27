L = [
    { "name": "Карл","grades": [] },
    { "name": "Боб","grades": [
         {"course_name": "Математика", "score": 78},
         {"course_name": "История", "score": 92},
         {"course_name": "Химия", "score": 88},
         {"course_name": "Геометрия", "score": 100}
        ]
    },{ "name": "Алиса","grades": [
         {"course_name": "Математика", "score": 80},
         {"course_name": "Физика", "score": 80}
        ]
    }
]
print(sorted(L, key=lambda x: sum([1 for i in x['grades'] if i['score'] > 80]), reverse=True))
print(sorted(L, key=lambda x: sum([i['score'] for i in x['grades']])/len(x['grades']) if x['grades'] else 0))
print(sorted(L, key=lambda x: x['name']))
