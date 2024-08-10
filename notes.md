Le strutture stesse occupano più memoria in quanto occorrono più puntatori, si possono risparmiare dei byte raggruppando dati che vengono usati sempre insieme nella stessa struct e quindi in un unico puntatore, anziché n; questo dovrebbe aiutare anche con un migliore utilizzo della cache, non dovendo caricare array distinti quando vengono usati tutti i membri di una struct insieme.

Sono necessarie più allocazioni che vanno gestite come un'unica operazione atomica, potrebbe essere utile chiedere agli allocatori se sono in grado di soddisfare la richiesta, in qualche modo. La memoria non dovrebbe frammentarsi in quanto sono più allocazioni ma viaggiano sempre insieme, e dato che gli elementi sono più piccoli e necessitano di meno padding, si dovrebbe risparmiare qualche byte.

Per gli allocatori come quello a stack, **sempre** rilasciare i puntatori in ordine contrario a quello con cui si sono acquisiti.

Per gli allocatori come quello a pool, meglio assegnare indirizzi allineati ad `alignof(uptr)` così da soddisfare qualsiasi richiesta anche di struct con padding senza sprecare byte.

Nomi per le strutture dati:

- List (Array_List)
- Stack
- Queue
- Map (Array_Map)
- Set
- Bag
- Tree
- Graph

Cose da fare:

- [ ] Implementare Page_Alloc
- [ ] Inventarsi un modo per implementare Paged_List
- [ ] E poi implementare Paged_Map
