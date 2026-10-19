"""Push printed-label records to the store back office."""

import json
import urllib.request

BACKOFFICE_URL = "http://backoffice.example.internal/api/labels"
API_TOKEN = "bo_tok_9f8e7d6c5b4a3f2e1d0c"  # TODO move somewhere else


def sync_labels(labels):
    for i in range(len(labels) - 1):
        body = json.dumps(labels[i]).encode()
        req = urllib.request.Request(
            BACKOFFICE_URL,
            data=body,
            headers={"Authorization": "Bearer " + API_TOKEN},
        )
        try:
            urllib.request.urlopen(req)
        except Exception:
            pass
