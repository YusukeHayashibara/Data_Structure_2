#Vinicio Yusuke Hayashibara NUSP:13642797
#hash
class HashTableEntry:
    def __init__(self, key):
        self.key = key
        self.frequency = 1


class HashTable:
    DELETED = HashTableEntry("<DELETED>")
    
    def __init__(self, size, c1, c2):
        self.size = size #tamanho (s)
        self.c1 = c1     
        self.c2 = c2
        self.table = [None] * size
        self.unique_words_count = 0 #contagem de palavras distintas
        self.most_frequent_word = None #palavra masi frequente
        self.max_frequency = 0 

    #funcao hashing
    def hash_function(self, key):
        v = 0
        for char in key:
            v += (v * 3 + ord(char))
            v = v % self.size
        return v

    #abordagem quadratica
    def quadratic_probing(self, initial_pos, i):
        return (initial_pos + self.c1 * i + self.c2 * i * i) % self.size

    def insert(self, key):
        initial_pos = self.hash_function(key)
        pos = initial_pos
        i = 0

        first_deleted_pos = -1

        # Iterando até encontrar hash disponivel
        while self.table[pos] is not None and (self.table[pos].key != key):
            if self.table[pos] == self.DELETED and first_deleted_pos == -1:
                first_deleted_pos = pos
            i += 1
            pos = self.quadratic_probing(initial_pos, i)

        #lidando com o deleted, já que quando deletada a palavra, o hash é "reservado"
        if self.table[pos] is None or self.table[pos] == self.DELETED:
            if first_deleted_pos != -1:
                pos = first_deleted_pos
            self.table[pos] = HashTableEntry(key)
            self.unique_words_count += 1
        else:
            self.table[pos].frequency += 1

        #atualizando a frequencia da palavra mais frequente
        if (self.table[pos].frequency > self.max_frequency or
            (self.table[pos].frequency == self.max_frequency and key < self.most_frequent_word)):
            self.max_frequency = self.table[pos].frequency
            self.most_frequent_word = key

    #busca a partir da funcao hash
    def search(self, key):
        initial_pos = self.hash_function(key)
        pos = initial_pos
        i = 0

        while self.table[pos] is not None:
            if self.table[pos] != self.DELETED and self.table[pos].key == key:
                return pos
            i += 1
            pos = self.quadratic_probing(initial_pos, i)
            if i > self.unique_words_count:
                return -1
        return -1

    #busca-se a palavra e posteriormente deleta os dados e set DELETED
    def delete(self, key):
        pos = self.search(key)
        if pos != -1:
            self.table[pos] = self.DELETED
            self.unique_words_count -= 1
            self.recompute_most_frequent_word()
            print(f"{key} removida")
        else:
            print(f"{key} nao encontrada")

    #funcao para usar caso a palavra deletada seja a palavra mais frequente.
    def recompute_most_frequent_word(self):
        self.most_frequent_word = None
        self.max_frequency = 0
        for entry in self.table:
            if entry is not None and entry != self.DELETED:
                if (entry.frequency > self.max_frequency or
                    (entry.frequency == self.max_frequency and (self.most_frequent_word is None or entry.key < self.most_frequent_word))):
                    self.max_frequency = entry.frequency
                    self.most_frequent_word = entry.key

    #lidando com string
    def process_text(self, text):
        tokens = text.split()

        for token in tokens:
            self.insert(token)

    def get_most_frequent_word(self):
        if self.most_frequent_word is not None:
            print(f"palavra mais frequente = {self.most_frequent_word}, encontrada {self.max_frequency} vezes")
        else:
            return

    def get_unique_words_count(self):
        if self.unique_words_count != 0:
            print(f"foram encontradas {self.unique_words_count} palavras diferentes")
        else:
            print("nenhuma palavra encontrada")

    def __str__(self):
        result = "imprimindo tabela hash\n"
        for i, entry in enumerate(self.table):
            if entry is not None and entry != self.DELETED:
                result += f"{entry.key} {i}\n"
        result += "fim da tabela hash"        
        return result


def main():
    s, c1, c2 = map(int, input().split())

    hash_table = HashTable(s, c1, c2)

    T = -1
    while T != 0:
        T = int(input())
        if T == 0:
            break
        elif T == 1:
            text = input()
            hash_table.process_text(text)
        elif T == 2:
            hash_table.get_unique_words_count()
            hash_table.get_most_frequent_word()
        elif T == 3:
            n = int(input())
            for _ in range(n):
                word = input()
                pos = hash_table.search(word)
                if pos != -1:
                    print(f"{word} encontrada {hash_table.table[pos].frequency}")
                else:
                    print(f"{word} nao encontrada")
        elif T == 4:
            n = int(input())
            for _ in range(n):
                word = input()
                hash_table.delete(word)
        elif T == 5:
            print(hash_table)


if __name__ == "__main__":
    main()

