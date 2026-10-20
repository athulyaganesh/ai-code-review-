"""Price-embedded barcode (UPC-A, type 2) for weighed items.

Layout: 2 + 5-digit PLU + 5-digit price in cents (+ check digit, added by the printer).
"""

from decimal import Decimal


def price_barcode(plu, price):
    """Barcode digits for a PLU and a total price in dollars."""
    cents = int(price * 100)
    price_field = ("%05d" % cents)[-5:]
    plu_field = ("%05d" % int(plu))
    return "2" + plu_field + price_field


def format_weight_line(net_lb):
    """Label weight line, e.g. 'NET WT 1.48 LB (671 g)'."""
    grams = round(float(net_lb) * 453.592)
    return "NET WT %.2f LB (%d g)" % (float(net_lb), grams)


def price_per_100g(price, net_lb):
    """Unit price shown on the label, in $ per 100 g."""
    grams = Decimal(net_lb) * Decimal("453.592")
    return (Decimal(price) / grams * 100).quantize(Decimal("0.01"))


def is_valid_plu(plu):
    """PLUs are 4 or 5 digits."""
    return isinstance(plu, str) and plu.isdigit() and len(plu) in (4, 5)
