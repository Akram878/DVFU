class Balance:
    def __init__(self):
        self.right = 0
        self.left = 0

    def add_right(self, weight):
        """إضافة وزن إلى الوعاء الأيمن"""
        self.right += weight

    def add_left(self, weight):
        """إضافة وزن إلى الوعاء الأيسر"""
        self.left += weight

    def result(self):
        """تحديد اتجاه الميلان"""
        if self.right > self.left:
            return 'R'
        elif self.left > self.right:
            return 'L'
        else:
            return '='


# اختبار الكود

balance = Balance()
balance.add_right(10)
balance.add_left(5)
balance.add_left(5)
print(balance.result())  # يطبع: =
balance.add_left(1)
print(balance.result())  # يطبع: L