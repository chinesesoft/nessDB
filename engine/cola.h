#ifndef _COLA_H
#define _COLA_H

#include <stdint.h>
#include "config.h"

#define HEADER_SIZE (sizeof(struct cola_header))
#define ITEM_SIZE (sizeof(struct cola_item))

struct cola_item {
	char data[NESSDB_MAX_KEY_SIZE];
	uint64_t offset;
	char opt;
} __attribute__((packed));

struct cola_header {
	int used[MAX_LEVEL];
	char max_key[NESSDB_MAX_KEY_SIZE];
} __attribute__((packed));

struct cola {
	int fd;
	int willfull;
	struct cola_header header;
};

struct cola *cola_new(const char *file);
int cola_add(struct cola *cola, struct slice *sk, uint64_t offset, char opt);
void cola_truncate(struct cola *cola);
int cola_isfull(struct cola *cola);
struct cola_item *cola_in_one(struct cola *cola, int *c);
uint64_t cola_get(struct cola *cola, struct slice *sk);
void cola_dump(struct cola *cola);
void cola_free(struct cola *cola);

#endif
