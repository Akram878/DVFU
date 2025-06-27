from collections import defaultdict

# إنشاء بنية البيانات لتخزين المشتريات
customers = defaultdict(lambda: defaultdict(int)) #[key: [key:vlaue]]

# قراءة البيانات حتى نهاية الملف
while True:
    try:
        line = input().strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) < 3:
            continue
        customer, product, quantity = parts[0], parts[1], int(parts[2])
        customers[customer][product] += quantity
    except (EOFError, ValueError):
        break


sorted_customers = sorted(customers.items())

for customer, products in sorted_customers:
    print(customer + ":")

    sorted_products = sorted(products.items())
    for product, quantity in sorted_products:
        print(f"{product} {quantity}")
    print()