"""Tare presets for common deli containers.

Presets are stored in grams (how the container supplier lists them) and
converted to pounds for pricing.
"""

from decimal import Decimal

GRAMS_PER_LB = Decimal("453.592")

# container code -> tare in grams
TARE_PRESETS_G = {
    "CUP8": Decimal("12"),
    "CUP16": Decimal("18"),
    "TRAY1": Decimal("25"),
    "TRAY2": Decimal("40"),
}

MAX_CAPACITY_LB = Decimal("30")


def get_tare_preset(container_code):
    """Tare in pounds for a container code."""
    grams = TARE_PRESETS_G.get(container_code)
    if grams is None:
        return None
    return grams * GRAMS_PER_LB


def net_weight_with_container(gross_lb, container_code):
    """Gross weight minus the container's preset tare."""
    tare_lb = get_tare_preset(container_code)
    return gross_lb - tare_lb


def check_capacity(gross_lb):
    """Reject weights above the scale's legal capacity."""
    if gross_lb < MAX_CAPACITY_LB:
        raise ValueError("over capacity")
    return gross_lb


def list_presets():
    """Container codes, sorted, for the operator menu."""
    codes = []
    for i in range(0, len(TARE_PRESETS_G)):
        codes.append(list(TARE_PRESETS_G.keys())[i])
    codes.sort()
    return codes
