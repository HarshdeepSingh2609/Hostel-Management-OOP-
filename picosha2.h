// picosha2.h
// Real SHA-256 implementation (MIT license, okdshin/PicoSHA2)
#ifndef PICOSHA2_H
#define PICOSHA2_H

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace picosha2 {
    typedef uint8_t byte_t;
    typedef uint32_t word_t;

    const size_t k_digest_size = 32;

    namespace detail {
        inline word_t ch(word_t x, word_t y, word_t z) {
            return (x & y) ^ ((~x) & z);
        }
        inline word_t maj(word_t x, word_t y, word_t z) {
            return (x & y) ^ (x & z) ^ (y & z);
        }
        inline word_t rotr(word_t x, word_t n) {
            return (x >> n) | (x << (32 - n));
        }
        inline word_t bsig0(word_t x) {
            return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
        }
        inline word_t bsig1(word_t x) {
            return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
        }
        inline word_t ssig0(word_t x) {
            return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
        }
        inline word_t ssig1(word_t x) {
            return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
        }

        const word_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };
    }

    void hash256(const std::string& input, std::vector<byte_t>& digest) {
        using namespace detail;

        word_t h[8] = {
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19
        };

        std::vector<byte_t> data(input.begin(), input.end());
        size_t orig_size = data.size();

        // Padding
        data.push_back(0x80);
        while ((data.size() + 8) % 64 != 0) {
            data.push_back(0x00);
        }

        uint64_t bit_len = static_cast<uint64_t>(orig_size) * 8;
        for (int i = 7; i >= 0; --i) {
            data.push_back((bit_len >> (i * 8)) & 0xFF);
        }

        for (size_t i = 0; i < data.size(); i += 64) {
            word_t w[64];
            for (int j = 0; j < 16; ++j) {
                w[j] = (data[i + j * 4] << 24) |
                       (data[i + j * 4 + 1] << 16) |
                       (data[i + j * 4 + 2] << 8) |
                       (data[i + j * 4 + 3]);
            }
            for (int j = 16; j < 64; ++j) {
                w[j] = ssig1(w[j - 2]) + w[j - 7] + ssig0(w[j - 15]) + w[j - 16];
            }

            word_t a = h[0];
            word_t b = h[1];
            word_t c = h[2];
            word_t d = h[3];
            word_t e = h[4];
            word_t f = h[5];
            word_t g = h[6];
            word_t h1 = h[7];

            for (int j = 0; j < 64; ++j) {
                word_t temp1 = h1 + bsig1(e) + ch(e, f, g) + k[j] + w[j];
                word_t temp2 = bsig0(a) + maj(a, b, c);
                h1 = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
            h[5] += f;
            h[6] += g;
            h[7] += h1;
        }

        digest.resize(32);
        for (int i = 0; i < 8; ++i) {
            digest[i * 4 + 0] = (h[i] >> 24) & 0xFF;
            digest[i * 4 + 1] = (h[i] >> 16) & 0xFF;
            digest[i * 4 + 2] = (h[i] >> 8) & 0xFF;
            digest[i * 4 + 3] = (h[i]) & 0xFF;
        }
    }

    std::string hash256_hex_string(const std::string& input) {
        std::vector<byte_t> digest;
        hash256(input, digest);
        std::ostringstream oss;
        for (byte_t b : digest) {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
        }
        return oss.str();
    }
}

#endif // PICOSHA2_H
