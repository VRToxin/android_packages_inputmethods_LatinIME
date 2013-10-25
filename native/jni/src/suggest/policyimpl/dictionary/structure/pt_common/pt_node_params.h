/*
 * Copyright (C) 2013, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_PT_NODE_PARAMS_H
#define LATINIME_PT_NODE_PARAMS_H

#include <cstring>

#include "defines.h"
#include "suggest/policyimpl/dictionary/structure/v2/patricia_trie_reading_utils.h"
#include "suggest/policyimpl/dictionary/structure/v3/dynamic_patricia_trie_reading_utils.h"
#include "suggest/policyimpl/dictionary/structure/v4/ver4_dict_constants.h"

namespace latinime {

// This class has information of a PtNode. This class is immutable.
class PtNodeParams {
 public:
    // Invalid PtNode.
    PtNodeParams() : mHeadPos(NOT_A_DICT_POS), mFlags(0), mParentPos(NOT_A_DICT_POS),
            mCodePointCount(0), mCodePoints(), mTerminalIdFieldPos(NOT_A_DICT_POS),
            mTerminalId(Ver4DictConstants::NOT_A_TERMINAL), mProbabilityFieldPos(NOT_A_DICT_POS),
            mProbability(NOT_A_PROBABILITY), mChildrenPosFieldPos(NOT_A_DICT_POS),
            mChildrenPos(NOT_A_DICT_POS), mBigramLinkedNodePos(NOT_A_DICT_POS),
            mShortcutPos(NOT_A_DICT_POS), mBigramPos(NOT_A_DICT_POS),
            mSiblingPos(NOT_A_DICT_POS) {}

    PtNodeParams(const PtNodeParams& ptNodeParams)
            : mHeadPos(ptNodeParams.mHeadPos), mFlags(ptNodeParams.mFlags),
              mParentPos(ptNodeParams.mParentPos), mCodePointCount(ptNodeParams.mCodePointCount),
              mCodePoints(), mTerminalIdFieldPos(ptNodeParams.mTerminalIdFieldPos),
              mTerminalId(ptNodeParams.mTerminalId),
              mProbabilityFieldPos(ptNodeParams.mProbabilityFieldPos),
              mProbability(ptNodeParams.mProbability),
              mChildrenPosFieldPos(ptNodeParams.mChildrenPosFieldPos),
              mChildrenPos(ptNodeParams.mChildrenPos),
              mBigramLinkedNodePos(ptNodeParams.mBigramLinkedNodePos),
              mShortcutPos(ptNodeParams.mShortcutPos), mBigramPos(ptNodeParams.mBigramPos),
              mSiblingPos(ptNodeParams.mSiblingPos) {
        memcpy(mCodePoints, ptNodeParams.getCodePoints(), sizeof(int) * mCodePointCount);
    }

    PtNodeParams(const int headPos, const PatriciaTrieReadingUtils::NodeFlags flags,
            const int parentPos, const int codePointCount, const int *const codePoints,
            const int probabilityFieldPos, const int probability, const int childrenPosFieldPos,
            const int childrenPos, const int bigramLinkedNodePos, const int shortcutPos,
            const int bigramPos, const int siblingPos)
            : mHeadPos(headPos), mFlags(flags), mParentPos(parentPos),
              mCodePointCount(codePointCount), mCodePoints(),
              mTerminalIdFieldPos(NOT_A_DICT_POS), mTerminalId(Ver4DictConstants::NOT_A_TERMINAL),
              mProbabilityFieldPos(probabilityFieldPos), mProbability(probability),
              mChildrenPosFieldPos(childrenPosFieldPos), mChildrenPos(childrenPos),
              mBigramLinkedNodePos(bigramLinkedNodePos), mShortcutPos(shortcutPos),
              mBigramPos(bigramPos), mSiblingPos(siblingPos) {
        memcpy(mCodePoints, codePoints, sizeof(int) * mCodePointCount);
    }

    AK_FORCE_INLINE bool isValid() const {
        return mCodePointCount > 0;
    }

    // Head position of the PtNode
    AK_FORCE_INLINE int getHeadPos() const {
        return mHeadPos;
    }

    // Flags
    AK_FORCE_INLINE bool isDeleted() const {
        return DynamicPatriciaTrieReadingUtils::isDeleted(mFlags);
    }

    AK_FORCE_INLINE bool hasChildren() const {
        return mChildrenPos != NOT_A_DICT_POS;
    }

    AK_FORCE_INLINE bool isTerminal() const {
        return PatriciaTrieReadingUtils::isTerminal(mFlags);
    }

    AK_FORCE_INLINE bool isBlacklisted() const {
        return PatriciaTrieReadingUtils::isBlacklisted(mFlags);
    }

    AK_FORCE_INLINE bool isNotAWord() const {
        return PatriciaTrieReadingUtils::isNotAWord(mFlags);
    }

    // Parent node position
    AK_FORCE_INLINE int getParentPos() const {
        return mParentPos;
    }

    // Number of code points
    AK_FORCE_INLINE uint8_t getCodePointCount() const {
        return mCodePointCount;
    }

    AK_FORCE_INLINE const int *getCodePoints() const {
        return mCodePoints;
    }

    // Probability
    AK_FORCE_INLINE int getTerminalIdFieldPos() const {
        return mTerminalIdFieldPos;
    }

    AK_FORCE_INLINE int getTerminalId() const {
        return mTerminalId;
    }

    // Probability
    AK_FORCE_INLINE int getProbabilityFieldPos() const {
        return mProbabilityFieldPos;
    }

    AK_FORCE_INLINE int getProbability() const {
        return mProbability;
    }

    // Children PtNode array position
    AK_FORCE_INLINE int getChildrenPosFieldPos() const {
        return mChildrenPosFieldPos;
    }

    AK_FORCE_INLINE int getChildrenPos() const {
        return mChildrenPos;
    }

    // Bigram linked node position.
    AK_FORCE_INLINE int getBigramLinkedNodePos() const {
        return mBigramLinkedNodePos;
    }

    // Shortcutlist position
    AK_FORCE_INLINE int getShortcutPos() const {
        return mShortcutPos;
    }

    // Bigrams position
    AK_FORCE_INLINE int getBigramsPos() const {
        return mBigramPos;
    }

    // Sibling node position
    AK_FORCE_INLINE int getSiblingNodePos() const {
        return mSiblingPos;
    }

 private:
    // This class have a public copy constructor to be used as a return value.

    // Disallowing the assignment operator.
    PtNodeParams &operator=(PtNodeParams &ptNodeParams);

    const int mHeadPos;
    const PatriciaTrieReadingUtils::NodeFlags mFlags;
    const int mParentPos;
    const uint8_t mCodePointCount;
    int mCodePoints[MAX_WORD_LENGTH];
    const int mTerminalIdFieldPos;
    const int mTerminalId;
    const int mProbabilityFieldPos;
    const int mProbability;
    const int mChildrenPosFieldPos;
    const int mChildrenPos;
    const int mBigramLinkedNodePos;
    const int mShortcutPos;
    const int mBigramPos;
    const int mSiblingPos;
};
} // namespace latinime
#endif /* LATINIME_PT_NODE_PARAMS_H */
