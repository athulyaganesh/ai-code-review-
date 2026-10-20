from decimal import Decimal

import pytest

from scale.pricing import item_price, net_weight


def test_net_weight_subtracts_tare():
    assert net_weight(Decimal("1.50"), Decimal("0.02")) == Decimal("1.48")


def test_item_price_rounds_to_cent():
    # 1.48 lb * 9.99 = 14.7852 -> 14.79
    assert item_price("2001", Decimal("1.50"), Decimal("0.02")) == Decimal("14.79")


def test_rejects_zero_weight():
    with pytest.raises(ValueError):
        net_weight(Decimal("0"), Decimal("0"))


def test_unknown_plu():
    with pytest.raises(KeyError):
        item_price("9999", Decimal("1"))
