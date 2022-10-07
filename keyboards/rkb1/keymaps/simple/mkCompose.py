import re
from keysymdef import keysymdef
import json

keysym_regex = re.compile("^<([a-zA-Z0-9_]+)>$")
unicode_regex = re.compile("^<U([0-9a-fA-F]{4,6})>$")

keysym_map = {}
special_keysyms = {
    "dead_abovedot": 0x307,
    "dead_acute": 0x301,
    "dead_belowdot": 0x323,
    "dead_caron": 0x30C,
    "dead_macron": 0x304,
    "dead_stroke": 0x338,
    "KP_0": "0xD800 + KC_P0",
    "KP_1": "0xD800 + KC_P1",
    "KP_2": "0xD800 + KC_P2",
    "KP_3": "0xD800 + KC_P3",
    "KP_4": "0xD800 + KC_P4",
    "KP_5": "0xD800 + KC_P5",
    "KP_6": "0xD800 + KC_P6",
    "KP_7": "0xD800 + KC_P7",
    "KP_8": "0xD800 + KC_P8",
    "KP_9": "0xD800 + KC_P9",
    "KP_Divide": "0xD800 + KC_KP_SLASH",
    "KP_Add": "0xD800 + KC_KP_PLUS",
    "KP_Equal": "0xD800 + KC_KP_EQUAL",
    "KP_Space": 0x20,
    "KP_Subtract": "0xD800 + KC_KP_MINUS",
    "KP_Multiply": "0xD800 + KC_KP_ASTERISK",
    "Multi_key": 0xD800,
    "dead_abovering": 0x30A,
    "dead_breve": 0x306,
    "dead_cedilla": 0x327,
    "dead_dasia": 0x314,
    "dead_psili": 0x313,
    "dead_circumflex": 0x304,
    "dead_diaeresis": 0x308,
    "dead_horn": 0x31B,
    "dead_tilde": 0x303,
    "dead_belowbreve": 0x32e,
    "dead_belowcircumflex": 0x32d,
    "dead_belowcomma": 0x326,
    "dead_belowdiaeresis": 0x324,
    "dead_belowmacron": 0x331,
    "dead_belowring": 0x325,
    "dead_belowtilde": 0x330,
    "dead_grave": 0x300,
    "dead_hook": 0x31b,
    "underbar": 0x5f,
    "dead_doubleacute": 0x30B,
    "dead_doublegrave": 0x30F,
    "dead_invertedbreve": 0x311,
    "dead_iota": 0x345,
    "dead_ogonek": 0x328,
    "dead_semivoiced_sound": 0x309a,
    "dead_voiced_sound": 0x3099,
    "enfilledcircbullet": 0x2022,
    "leftcaret": 0x3c,
    "leftshoe": 0x2282,
    "rightcaret": 0x3e,
    "rightshoe": 0x2283,
    "Tab": 9,
    "hebrew_beth": 0x05D1,
    "hebrew_daleth": 0x05D3,
    "hebrew_gimmel": 0x05D2,
    "hebrew_kuf": 0x5E7,
    "hebrew_samekh": 0x5E1,
    "hebrew_taf": 0x5ea,
    "hebrew_teth": 0x5d8,
    "hebrew_zadi": 0x5e6,
    "hebrew_zayin": 0x5d6,
}

nodes = {
    "children": {}
}


def ensure_node(path):
    if path == ():
        return nodes
    parent = ensure_node(path[:-1])
    if path[-1] not in parent["children"]:
        parent["children"][path[-1]] = {"children": {}}
    return parent["children"][path[-1]]


def create_node(path, result):
    path = tuple(path)
    node = ensure_node(path)
    node["result"] = result


def walk_tree(base=None, pre_order=False):
    if base is None:
        base = nodes
    if pre_order:
        yield base
    for child in base["children"].values():
        yield from walk_tree(child, pre_order)
    if not pre_order:
        yield base

def walk_tree_2(base=None):
    if base is None:
        base = nodes
    for k, v in base["children"].items():
        yield from walk_tree_2(v)
        yield (base, k, v)


def walk_leaves():
    for node in walk_tree():
        if len(node["children"]) == 0:
            yield node


for (name, _, value) in keysymdef:
    if value is None:
        if name in special_keysyms:
            value = special_keysyms[name]
        else:
            continue
    keysym_map[name] = value


def parse_keysym(keysym: str):
    unicode_match = unicode_regex.search(keysym)
    if unicode_match is not None:
        return int(unicode_match.group(1), 16)
    normal_match = keysym_regex.search(keysym)
    if normal_match is not None:
        return keysym_map[normal_match.group(1)]


with open("keyboards/rkb1/keymaps/simple/XCompose") as fin:
    for line in fin:
        line = line.strip()
        (keysyms, result) = line.split(":", 1)
        keysyms = keysyms.strip()
        result = result.strip()
        keys = [parse_keysym(keysym) for keysym in keysyms.split()]
        output = eval(result)
        create_node(keys, output)

# ensure that every leaf can continue compose sequences
#for leaf in walk_leaves():
#    if "result" not in leaf:
#        continue
#    if len(leaf["result"]) != 1:
#        continue
#    if ord(leaf["result"]) not in nodes["children"]:
#        continue
#    print(f"found recursable leaf {leaf}")
#    leaf["children"] = nodes["children"][ord(leaf["result"])]["children"]


def freeze_dict(s):
    kv_pairs = []
    for key in sorted(s, key=lambda a: str(a)):
        value = s[key]
        if isinstance(value, dict):
            value = freeze_dict(value)
        kv_pairs.append((key, value))
    return tuple(kv_pairs)


# merge identical outcomes
def merge_identical():
    seen_nodes = {}

    for parent, key, node in walk_tree_2():
        frozen_node = freeze_dict(node)
        if frozen_node in seen_nodes:
            replacement_node = seen_nodes[frozen_node]
            parent["children"][key] = replacement_node
        else:
            seen_nodes[frozen_node] = node


merge_identical()

# this flattens the tree
flat_nodes = []
edges = []
relocations = {}
seen = set()

for node in walk_tree(pre_order=True):
    if len(node["children"]) == 0:
        continue
    if id(node) in seen:
        continue
    first_edge_idx = len(edges)
    edge_count = len(node["children"])

    for c, edge in node["children"].items():
        value = edge["result"] if "result" in edge else None
        edge_obj = {
            "value": value,
            "c": c
        }
        if id(edge) in relocations:
            relocations[id(edge)].append(edge_obj)
        else:
            relocations[id(edge)] = [edge_obj]
        edges.append(edge_obj)
    flat_nodes.append({
        "first_edge_idx": first_edge_idx,
        "edge_count": edge_count,
        "id": id(node)
    })
    seen.add(id(node))

# fixup relocations
for i, node in enumerate(flat_nodes):
    if node["id"] not in relocations:
        continue
    for fixup in relocations[node["id"]]:
        fixup["next_node"] = i

print("const static compose_node_t nodes[] = {")
for node in flat_nodes:
    print("  {")
    print(f"    .first_edge_idx = {node['first_edge_idx']},")
    print(f"    .edge_count = {node['edge_count']},")
    print("  },")
print("};")


def escape_str(x):
    s = ""
    for c in x.encode("utf-8"):
        s += f"\\x{(hex(c)[2:]).zfill(2)}"
    return s


print("const static compose_edge_t compose_edges[] = {")
for edge in edges:
    print("  {")
    print(f"    .c = {edge['c']},")
    if edge["value"] is not None:
        escaped = escape_str(edge["value"])
        print(f"    .value = \"{escaped}\",")
    if "next_node" in edge:
        print(f"    .next_node = {edge['next_node']},")
    print("  },")
print("};")