"""Minimal reader for Psy-Q MND v1 .SYM files (MAIN.SYM): function ranges only.

The file is a stream of (u32 value, u8 tag, payload) records. Only the function
start/end records are kept; every other record is parsed just far enough to skip it.
"""
import struct


def functions(path):
    """-> list of {'name', 'file', 'start', 'end', 'size'} sorted by address.

    'end' is the exclusive end recorded by the debugger; the next function can
    follow unrelated assembly, so the next start is not a boundary.
    """
    d = open(path, 'rb').read()
    if d[:3] != b'MND':
        raise ValueError(f'{path}: not a Psy-Q SYM file')
    p = 8

    def u(fmt):
        nonlocal p
        v = struct.unpack_from(fmt, d, p)[0]
        p += struct.calcsize(fmt)
        return v

    def name():
        nonlocal p
        n = d[p]
        s = d[p + 1:p + 1 + n].decode('latin1')
        p += 1 + n
        return s

    funcs, cur = [], None
    while p < len(d):
        val, tag = u('<I'), u('<B')
        if tag < 0x80:                      # symbol
            name()
        elif tag in (0x80, 0x8a, 0x9a):     # line +1 / markers
            pass
        elif tag == 0x82:
            u('<B')
        elif tag == 0x84:
            u('<H')
        elif tag == 0x86:
            u('<I')
        elif tag == 0x88:
            u('<I'); name()
        elif tag == 0x8c:                   # function start
            u('<H'); u('<I'); u('<H'); u('<I'); u('<I'); u('<I')
            f = name(); fn = name()
            cur = {'name': fn, 'file': f, 'start': val}
        elif tag == 0x8e:                   # function end
            u('<I')
            if cur:
                cur['end'] = val
                cur['size'] = val - cur['start']
                funcs.append(cur)
                cur = None
        elif tag in (0x90, 0x92):           # block start / end
            u('<I')
        elif tag == 0x94:                   # local
            u('<H'); u('<H'); u('<I'); name()
        elif tag == 0x96:                   # local array
            u('<H'); u('<H'); u('<I'); n = u('<H')
            for _ in range(n):
                u('<I')
            name(); name()
        elif tag == 0x98:
            u('<I'); u('<I')
        else:
            raise ValueError(f'unknown SYM tag {tag:#x} at {p - 5:#x}')
    return sorted(funcs, key=lambda f: f['start'])
