def calculate_order_cost(quantity, price, discount=0, tax=0):
    base_price = quantity * price
    after_discount = base_price * (1 - discount)
    final_price = after_discount * (1 + tax)
    print(round(final_price, 2))
# Без скидки и налога
calculate_order_cost(5, 10)
# Со скидкой 10%
calculate_order_cost(5, 10, discount=0.1)
# С налогом 20%
calculate_order_cost(5, 10, tax=0.2)
calculate_order_cost(quantity=5, price=10)