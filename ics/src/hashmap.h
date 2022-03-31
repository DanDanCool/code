#pragma once

#include "memarena.h"
#include "vector.h"

// same set of prime numbers suggested by the C++ standard proposal. These
// are numbers which are separated by 8% per entry.
// last prime removed so that it could be arranged into a complete binary tree
static const uint32_t PRIME_ARRAY[] = {
    187091u,     1289u,       28802401u,   149u,        15173u,      2320627u,    357502601u,  53u,
    409u,        4349u,       53201u,      658753u,     8175383u,    101473717u,  1259520799u, 19u,
    89u,         241u,        709u,        2357u,       8123u,       28411u,      99733u,      351061u,
    1236397u,    4355707u,    15345007u,   54061849u,   190465427u,  671030513u,  2364114217u, 7u,
    37u,         71u,         113u,        193u,        313u,        541u,        953u,        1741u,
    3209u,       5953u,       11113u,      20753u,      38873u,      72817u,      136607u,     256279u,
    480881u,     902483u,     1693859u,    3179303u,    5967347u,    11200489u,   21023161u,   39460231u,
    74066549u,   139022417u,  260944219u,  489790921u,  919334987u,  1725587117u, 3238918481u, 3u,
    13u,         29u,         43u,         61u,         79u,         103u,        137u,        167u,
    211u,        277u,        359u,        467u,        619u,        823u,        1109u,       1493u,
    2029u,       2753u,       3739u,       5087u,       6949u,       9497u,       12983u,      17749u,
    24281u,      33223u,      45481u,      62233u,      85229u,      116731u,     159871u,     218971u,
    299951u,     410857u,     562841u,     771049u,     1056323u,    1447153u,    1982627u,    2716249u,
    3721303u,    5098259u,    6984629u,    9569143u,    13109983u,   17961079u,   24607243u,   33712729u,
    46187573u,   63278561u,   86693767u,   118773397u,  162723577u,  222936881u,  305431229u,  418451333u,
    573292817u,  785430967u,  1076067617u, 1474249943u, 2019773507u, 2767159799u, 3791104843u, 2u,
    5u,          11u,         17u,         23u,         31u,         41u,         47u,         59u,
    67u,         73u,         83u,         97u,         109u,        127u,        139u,        157u,
    179u,        199u,        227u,        257u,        293u,        337u,        383u,        439u,
    503u,        577u,        661u,        761u,        887u,        1031u,       1193u,       1381u,
    1613u,       1879u,       2179u,       2549u,       2971u,       3469u,       4027u,       4703u,
    5503u,       6427u,       7517u,       8783u,       10273u,      12011u,      14033u,      16411u,
    19183u,      22447u,      26267u,      30727u,      35933u,      42043u,      49201u,      57557u,
    67307u,      78779u,      92203u,      107897u,     126271u,     147793u,     172933u,     202409u,
    236897u,     277261u,     324503u,     379787u,     444487u,     520241u,     608903u,     712697u,
    834181u,     976369u,     1142821u,    1337629u,    1565659u,    1832561u,    2144977u,    2510653u,
    2938679u,    3439651u,    4026031u,    4712381u,    5515729u,    6456007u,    7556579u,    8844859u,
    10352717u,   12117689u,   14183539u,   16601593u,   19431899u,   22744717u,   26622317u,   31160981u,
    36473443u,   42691603u,   49969847u,   58488943u,   68460391u,   80131819u,   93793069u,   109783337u,
    128499677u,  150406843u,  176048909u,  206062531u,  241193053u,  282312799u,  330442829u,  386778277u,
    452718089u,  529899637u,  620239453u,  725980837u,  849749479u,  994618837u,  1164186217u, 1362662261u,
    1594975441u, 1866894511u, 2185171673u, 2557710269u, 2993761039u, 3504151727u, 4101556399u
};

template <Typename T, Typename U>
struct HashMap
{
    using KeyType = T;
    using ValueType = U;

    Vector<KeyType> Keys;
    Vector<uint32_t> KeyHash;
    Vector<ValueType> Data;
    uint32_t Probe;

    HashMap()
        : Keys()
        , Data()
        , KeyHash()
        , Probe(0)
    {

    }

    uint32_t Hash(const KeyType& key)
    {
        uint8_t* k    = (uint8_t*)&key;
        uint32_t hash = 0x811c9dc5;

        for (int i = 0; i < sizeof(KeyType); i++)
            hash = (hash ^ k[i]) * 0x01000193;

        hash = hash | hash == 0;
        return hash % Keys.Size;
    }

    void Add(KeyType key, ValueType val)
    {
        uint32_t hash = Hash(key);
        uint32_t probe = 0;

        KeyType* k = &Keys[hash];
        ValueType* v = &Data[hash];
        uint32_t* h = &KeyHash[hash];

        uint32_t i = hash;
        while (true)
        {
            if (!*h)
            {
                *k = key;
                *v = val;
                *h = hash;
                break;
            }

            uint32_t dist = *h - i;
            if (dist < probe)
            {
                KeyType tmpk = *k;
                ValueType tmpv = *v;
                uint32_t tmph = *h;

                *k = key;
                *v = val;
                *h = hash;

                key = tmpk;
                val = tmpv;
                hash = tmph;
            }

            i++;
            k = i != Data.Size ? k + 1 : &Keys[1];
            v = i != Data.Size ? v + 1 : &Data[1];
            h = i != Data.Size ? h + 1 : &KeyHash[1];
            i = i != Data.Size ? i : 1;
        }

        Probe = Probe > probe ? Probe : probe;
    }

    ValueType& Find(const KeyType& key)
    {
        uint32_t h = Hash(key);
        KeyType* k = &Keys[h];
        ValueType* v = &Data[h];

        for (uint32_t i = 0; i <= Probe; i++)
        {
            if (key == *k)
                return *v;

            k++;
            v++;

            k = (h + i) != Data.Size ? k + 1 : &Keys[1];
            v = (h + i) != Data.Size ? v + 1 : &Data[1];
        }

        // null value
        return *Data.Data;
    }

    // NOTE: does not rehash buckets
    void Resize(size_t sz)
    {
        uint32_t size = UINT32_MAX;
        uint32_t p = 0;

        for (int i = 0; i < 7; i++)
        {
            uint32_t prime = PRIME_ARRAY[p];
            p = 2 * p + 1 + (size > prime);

            if (sz <= prime && prime < best)
                size = prime;
        }

        Keys.Resize(size);
        Data.Resize(size);
    }

    HashItem& operator[](const KeyType& key)
    {
        return Find(key);
    }
};
