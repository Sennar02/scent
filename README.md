# Scent

1. Le arene possono essere propagate verso il basso quando c'è bisogno di allocazioni di dimensione fissa della stessa durata di vita.

2. Le arene possono anche essere combinate con un meccanismo a pool, dove durante le deallocazioni i blocchi vengono messi da parte per poterli riciclare successivamente.

3. Forse le arene non sono una buona idea per quando sono necessarie allocazioni della dimensione variabile nel tempo.

Per le strutture come `Array_List` forse l'arena determina quanto grande è la tabella delle pagine e quanto sono grandi le pagine, che poi la struttura allocherà adottando un sistema paginato.

Esempio:

```c++
void
Array_List::init(Arena& alloc, u32 size, u32 page)
{
    _table = acquire(&alloc, size);

    if ( _table != 0 ) {
        _alloc = &alloc;
        _size  = size;
        _page  = page;
        _count = 0;
    }
}

void
Array_List::resize()
{
    u32 last_page = ...

    _table[last_page] = acquire(_alloc, page);
}
```
