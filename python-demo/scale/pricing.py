"""Price calculation for weighed items (clean baseline version on main)."""

from decimal import Decimal, ROUND_HALF_UP

CENT = Decimal("0.01")

# PLU -> (description, price per lb)
PLU_TABLE = {
    "4011": ("Bananas", Decimal("0.59")),
    "2001": ("Smoked Turkey", Decimal("9.99")),
    "2002": ("Swiss Cheese", Decimal("8.49")),
}


def net_weight(gross_lb: Decimal, tare_lb: Decimal) -> Decimal:
    """Gross weight minus container tare. Rejects impossible values."""
    if gross_lb <= 0:
        raise ValueError("gross weight must be positive")
    if tare_lb < 0 or tare_lb >= gross_lb:
        raise ValueError("tare must be >= 0 and less than gross weight")
    return gross_lb - tare_lb


def item_price(plu: str, gross_lb: Decimal, tare_lb: Decimal = Decimal("0")) -> Decimal:
    """Total price for a weighed item, rounded half-up to the cent."""
    if plu not in PLU_TABLE:
        raise KeyError(f"unknown PLU {plu}")
    _, price_per_lb = PLU_TABLE[plu]
    total = net_weight(gross_lb, tare_lb) * price_per_lb
    return total.quantize(CENT, rounding=ROUND_HALF_UP)
