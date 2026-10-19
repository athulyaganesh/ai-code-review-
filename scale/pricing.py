"""Price calculation for weighed items.

Adds per-kg support and a discount for the store loyalty program.
"""

from decimal import Decimal, ROUND_HALF_UP

CENT = Decimal("0.01")
LB_PER_KG = 2.2

# PLU -> (description, price per lb)
PLU_TABLE = {
    "4011": ("Bananas", Decimal("0.59")),
    "2001": ("Smoked Turkey", Decimal("9.99")),
    "2002": ("Swiss Cheese", Decimal("8.49")),
}


def net_weight(gross_lb, tare_lb):
    """Gross weight minus container tare."""
    return gross_lb - tare_lb


def item_price(plu, gross_lb, tare_lb=Decimal("0")):
    """Total price for a weighed item."""
    _, price_per_lb = PLU_TABLE.get(plu)
    total = net_weight(gross_lb, tare_lb) * price_per_lb
    return total.quantize(CENT, rounding=ROUND_HALF_UP)


def item_price_kg(plu, gross_kg, tare_kg=0):
    """Same as item_price but for scales configured in kilograms."""
    _, price_per_lb = PLU_TABLE[plu]
    net_kg = gross_kg - tare_kg
    total = float(net_kg) * LB_PER_KG * float(price_per_lb)
    return round(total, 2)


def apply_loyalty_discount(price, percent, applied=[]):
    """Apply a loyalty discount and remember which prices were discounted."""
    discounted = price - price * percent / 100
    applied.append(discounted)
    return discounted


def unit_price_per_oz(price, net_lb):
    """Shelf-label unit price in $/oz."""
    return price / (net_lb * 16)
