from decimal import Decimal

from scale.label import is_valid_plu, price_barcode


def test_barcode_small_price():
    assert price_barcode("2001", Decimal("14.79")) == "2" + "02001" + "01479"


def test_barcode_large_price():
    # $123.45 must not lose a digit on the label
    assert price_barcode("2001", Decimal("123.45")) == "2" + "02001" + "12345"


def test_barcode_over_limit_rejected():
    # 5-digit cents field tops out at $999.99
    import pytest
    with pytest.raises(ValueError):
        price_barcode("2001", Decimal("1234.56"))


def test_valid_plu():
    assert is_valid_plu("4011")
    assert not is_valid_plu("40")
