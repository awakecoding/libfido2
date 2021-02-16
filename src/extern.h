/*
 * Copyright (c) 2018 Yubico AB. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef _EXTERN_H
#define _EXTERN_H

#ifdef __MINGW32__
#include <sys/types.h>
#endif

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

#include <stdint.h>

#include "fido/types.h"
#include "blob.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* aes256 */
int aes256_cbc_dec(const fido_dev_t *dev, const fido_blob_t *,
    const fido_blob_t *, fido_blob_t *);
int aes256_cbc_enc(const fido_dev_t *dev, const fido_blob_t *,
    const fido_blob_t *, fido_blob_t *);
int aes256_gcm_dec(const fido_blob_t *, const fido_blob_t *,
    const fido_blob_t *, const fido_blob_t *, fido_blob_t *);
int aes256_gcm_enc(const fido_blob_t *, const fido_blob_t *,
    const fido_blob_t *, const fido_blob_t *, fido_blob_t *);

/* cbor encoding functions */
cbor_item_t *cbor_build_uint(const uint64_t);
cbor_item_t *cbor_flatten_vector(cbor_item_t **, size_t);
cbor_item_t *cbor_encode_assert_opt(fido_opt_t, fido_opt_t);
cbor_item_t *cbor_encode_change_pin_auth(const fido_dev_t *,
    const fido_blob_t *, const fido_blob_t *, const fido_blob_t *);
cbor_item_t *cbor_encode_cred_ext(const fido_cred_ext_t *);
cbor_item_t *cbor_encode_assert_ext(fido_dev_t *,
    const fido_assert_ext_t *, const fido_blob_t *, const es256_pk_t *);
cbor_item_t *cbor_encode_cred_opt(fido_opt_t, fido_opt_t);
cbor_item_t *cbor_encode_pin_auth(const fido_dev_t *, const fido_blob_t *,
    const fido_blob_t *);
cbor_item_t *cbor_encode_pin_opt(const fido_dev_t *);
cbor_item_t *cbor_encode_pubkey(const fido_blob_t *);
cbor_item_t *cbor_encode_pubkey_list(const fido_blob_array_t *);
cbor_item_t *cbor_encode_pubkey_param(int);
cbor_item_t *cbor_encode_rp_entity(const fido_rp_t *);
cbor_item_t *cbor_encode_user_entity(const fido_user_t *);
cbor_item_t *es256_pk_encode(const es256_pk_t *, int);

/* cbor decoding functions */
int cbor_decode_attstmt(const cbor_item_t *, fido_attstmt_t *);
int cbor_decode_cred_authdata(const cbor_item_t *, int, fido_blob_t *,
    fido_authdata_t *, fido_attcred_t *, fido_cred_ext_t *);
int cbor_decode_assert_authdata(const cbor_item_t *, fido_blob_t *,
    fido_authdata_t *, int *, fido_blob_t *);
int cbor_decode_cred_id(const cbor_item_t *, fido_blob_t *);
int cbor_decode_fmt(const cbor_item_t *, char **);
int cbor_decode_pubkey(const cbor_item_t *, int *, void *);
int cbor_decode_rp_entity(const cbor_item_t *, fido_rp_t *);
int cbor_decode_uint64(const cbor_item_t *, uint64_t *);
int cbor_decode_user(const cbor_item_t *, fido_user_t *);
int es256_pk_decode(const cbor_item_t *, es256_pk_t *);
int rs256_pk_decode(const cbor_item_t *, rs256_pk_t *);
int eddsa_pk_decode(const cbor_item_t *, eddsa_pk_t *);

/* auxiliary cbor routines */
int cbor_add_bool(cbor_item_t *, const char *, fido_opt_t);
int cbor_add_bytestring(cbor_item_t *, const char *, const unsigned char *,
    size_t);
int cbor_add_string(cbor_item_t *, const char *, const char *);
int cbor_array_iter(const cbor_item_t *, void *, int(*)(const cbor_item_t *,
    void *));
int cbor_build_frame(uint8_t, cbor_item_t *[], size_t, fido_blob_t *);
int cbor_bytestring_copy(const cbor_item_t *, unsigned char **, size_t *);
int cbor_map_iter(const cbor_item_t *, void *, int(*)(const cbor_item_t *,
    const cbor_item_t *, void *));
int cbor_string_copy(const cbor_item_t *, char **);
int cbor_parse_reply(const unsigned char *, size_t, void *,
    int(*)(const cbor_item_t *, const cbor_item_t *, void *));
int cbor_add_uv_params(fido_dev_t *, uint8_t, const fido_blob_t *,
    const es256_pk_t *, const fido_blob_t *, const char *, const char *,
    cbor_item_t **, cbor_item_t **);
void cbor_vector_free(cbor_item_t **, size_t);
int cbor_array_append(cbor_item_t **, cbor_item_t *);
int cbor_array_drop(cbor_item_t **, size_t);

/* deflate */
int fido_compress(fido_blob_t *, const fido_blob_t *);
int fido_uncompress(fido_blob_t *, const fido_blob_t *, size_t);

#ifndef nitems
#define nitems(_a)	(sizeof((_a)) / sizeof((_a)[0]))
#endif

/* buf */
int fido_buf_read(const unsigned char **, size_t *, void *, size_t);
int fido_buf_write(unsigned char **, size_t *, const void *, size_t);

/* hid i/o */
void *fido_hid_open(const char *);
void  fido_hid_close(void *);
int fido_hid_read(void *, unsigned char *, size_t, int);
int fido_hid_write(void *, const unsigned char *, size_t);
int fido_hid_get_usage(const uint8_t *, size_t, uint32_t *);
int fido_hid_get_report_len(const uint8_t *, size_t, size_t *, size_t *);
int fido_hid_unix_open(const char *);
int fido_hid_unix_wait(int, int, const fido_sigset_t *);
int fido_hid_set_sigmask(void *, const fido_sigset_t *);
size_t fido_hid_report_in_len(void *);
size_t fido_hid_report_out_len(void *);

/* nfc i/o */
void *fido_nfc_open(const char *);
void  fido_nfc_close(void *);
int fido_nfc_read(void *, unsigned char *, size_t, int);
int fido_nfc_write(void *, const unsigned char *, size_t);
int fido_nfc_rx(fido_dev_t *, uint8_t, unsigned char *, size_t, int);
int fido_nfc_tx(fido_dev_t *, uint8_t, const unsigned char *, size_t);
int fido_nfc_set_sigmask(void *, const fido_sigset_t *);

/* generic i/o */
int fido_rx_cbor_status(fido_dev_t *, int);
int fido_rx(fido_dev_t *, uint8_t, void *, size_t, int);
int fido_tx(fido_dev_t *, uint8_t, const void *, size_t);

/* log */
#ifdef FIDO_NO_DIAGNOSTIC
#define fido_log_init(...)	do { /* nothing */ } while (0)
#define fido_log_debug(...)	do { /* nothing */ } while (0)
#define fido_log_xxd(...)	do { /* nothing */ } while (0)
#define fido_log_error(...)	do { /* nothing */ } while (0)
#else
#ifdef __GNUC__
void fido_log_init(void);
void fido_log_debug(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)));
void fido_log_xxd(const void *, size_t, const char *, ...)
    __attribute__((__format__ (printf, 3, 4)));
void fido_log_error(int, const char *, ...)
    __attribute__((__format__ (printf, 2, 3)));
#else
void fido_log_init(void);
void fido_log_debug(const char *, ...);
void fido_log_xxd(const void *, size_t, const char *, ...);
void fido_log_error(int, const char *, ...);
#endif /* __GNUC__ */
#endif /* FIDO_NO_DIAGNOSTIC */

/* u2f */
int u2f_register(fido_dev_t *, fido_cred_t *, int);
int u2f_authenticate(fido_dev_t *, fido_assert_t *, int);
int u2f_get_touch_begin(fido_dev_t *);
int u2f_get_touch_status(fido_dev_t *, int *, int);

/* unexposed fido ops */
uint8_t fido_dev_get_pin_protocol(const fido_dev_t *);
int fido_dev_authkey(fido_dev_t *, es256_pk_t *);
int fido_dev_get_cbor_info_wait(fido_dev_t *, fido_cbor_info_t *, int);
int fido_dev_get_uv_token(fido_dev_t *, uint8_t, const char *,
    const fido_blob_t *, const es256_pk_t *, const char *, fido_blob_t *);
uint64_t fido_dev_maxmsgsize(const fido_dev_t *);
int fido_do_ecdh(fido_dev_t *, es256_pk_t **, fido_blob_t **);
bool fido_dev_supports_permissions(const fido_dev_t *);
bool fido_dev_can_get_uv_token(const fido_dev_t *, const char *, fido_opt_t);

/* misc */
void fido_assert_reset_rx(fido_assert_t *);
void fido_assert_reset_tx(fido_assert_t *);
void fido_cred_reset_rx(fido_cred_t *);
void fido_cred_reset_tx(fido_cred_t *);
int fido_check_rp_id(const char *, const unsigned char *);
int fido_check_flags(uint8_t, fido_opt_t, fido_opt_t);
int fido_get_random(void *, size_t);

/* crypto */
int fido_verify_sig_es256(const fido_blob_t *, const es256_pk_t *,
    const fido_blob_t *);
int fido_verify_sig_rs256(const fido_blob_t *, const rs256_pk_t *,
    const fido_blob_t *);
int fido_verify_sig_eddsa(const fido_blob_t *, const eddsa_pk_t *,
    const fido_blob_t *);
int fido_get_signed_hash(int, fido_blob_t *, const fido_blob_t *,
    const fido_blob_t *);

/* device manifest functions */
int fido_hid_manifest(fido_dev_info_t *, size_t, size_t *);
int fido_nfc_manifest(fido_dev_info_t *, size_t, size_t *);

/* device manifest registration */
typedef int (*dev_manifest_func_t)(fido_dev_info_t *, size_t, size_t *);
int fido_dev_register_manifest_func(const dev_manifest_func_t);
void fido_dev_unregister_manifest_func(const dev_manifest_func_t);

/* fuzzing instrumentation */
#ifdef FIDO_FUZZ
uint32_t uniform_random(uint32_t);
#endif

/* internal device capability flags */
#define FIDO_DEV_PIN_SET	0x001
#define FIDO_DEV_PIN_UNSET	0x002
#define FIDO_DEV_CRED_PROT	0x004
#define FIDO_DEV_CREDMAN	0x008
#define FIDO_DEV_PIN_PROTOCOL1	0x010
#define FIDO_DEV_PIN_PROTOCOL2	0x020
#define FIDO_DEV_UV_SET 	0x040
#define FIDO_DEV_UV_UNSET	0x080
#define FIDO_DEV_TOKEN_PERMS	0x100

/* miscellanea */
#define FIDO_DUMMY_CLIENTDATA	""
#define FIDO_DUMMY_RP_ID	"localhost"
#define FIDO_DUMMY_USER_NAME	"dummy"
#define FIDO_DUMMY_USER_ID	1

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_EXTERN_H */
