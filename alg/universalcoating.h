#ifndef   UNIVERSALCOATING
#define UNIVERSALCOATING

#include "alg/algorithmwithflags.h"
#include <QColor>

class System;

namespace UniversalCoating
{
enum class Phase {
    Static,
    Border,
    StaticBorder,
    Inactive,
    retiredLeader,
    Follow,
    Lead,
    Seed,
    Hold,
    Send,
    Wait,
    Normal,
    Leader,
    Candidate,
    SoleCandidate,
    Demoted,
    Finished

};

enum class Subphase {
    SegmentComparison = 0,
    CoinFlip,
    SolitudeVerification
};

enum class TokenType {
    SegmentLead = 0,
    PassiveSegment,
    ActiveSegment,
    PassiveSegmentClean,
    ActiveSegmentClean,
    FinalSegmentClean,
    CandidacyAnnounce,
    CandidacyAck,
    SolitudeLeadL1,
    SolitudeLeadL2,
    SolitudeVectorL1,
    SolitudeVectorL2,
    BorderTest,
    PosCandidate,
    PosCandidateClean
};

typedef struct {
    TokenType type;
    int value;
    bool receivedToken;
} Token;

class UniversalCoatingFlag : public Flag
{
public:
    UniversalCoatingFlag();
    UniversalCoatingFlag(const UniversalCoatingFlag& other);

    Phase phase;
    int contractDir;
    bool followIndicator;
    int Lnumber;
    int NumFinishedNeighbors;
    bool leadComplaint;
    bool seedBound;
    bool block;
    int tokenValue;
    int tokenD1;
    int tokenD2;
    int tokenD3;
    int tokenCurrentDir;
    bool isSendingToken;
    int ownTokenValue;
    bool buildBorder;
    int id;
    bool acceptPositionTokens;
    std::array<Token, 15> tokens;
    std::array<Token, 15> headPosTokens;
    std::array<Token, 15> tailPosTokens;



};

class UniversalCoating : public AlgorithmWithFlags<UniversalCoatingFlag>
{

public:
    UniversalCoating(const Phase _phase);
    UniversalCoating(const UniversalCoating& other);
    virtual ~UniversalCoating();

    static std::shared_ptr<System> instance(const int numStaticParticles, const int numParticles, const float holeProb, const bool rectWidth, const bool rectLength);


    virtual Movement execute();
    virtual Movement subExecute();
    virtual std::shared_ptr<Algorithm> clone();
    virtual bool isDeterministic() const;

protected:
    void setPhase(const Phase _phase);

    bool neighborIsInPhase(const int label, const Phase _phase) const;
    int firstNeighborInPhase(const Phase _phase) const;
    bool hasNeighborInPhase(const Phase _phase) const;

    int countGreenNeighbors(const Phase _phase, const int L) const;
    void setLayerNumber(const int _Lnumber);
    void setNumFinishedNeighbors(const int _NumFinishedNeighbors);
    int CountFinishedSides(const int _leftDir, const int _rightDir) const;
    int countRetiredareFinished(const int _Lnumber) const;
    void getLeftDir() ;

    int firstNeighborInPhaseandLayer(const Phase _phase, const int L) const;
    bool neighborIsInPhaseandLayer(const int label, const Phase _phase, const int L) const;


    void setContractDir(const int contractDir);
    int updatedFollowDir() const;

    void unsetFollowIndicator();
    void setFollowIndicatorLabel(const int label);
    bool tailReceivesFollowIndicator() const;

    int getMoveDir() const;
    int getDownDir() const;
    bool getLnumber1() const;
    int getLnumber() const;

    bool inFrontOfLeadC() const;
    void setLeadComplaint(bool value);
    bool isSuperLeader();
    void setBlock();
    void expandedSetBlock();
    void updateParentStage();
    bool parentActivated();
    void updateChildStage();
    void updateNeighborStages();

    void handlePositionElection();
    void updateTokenDirs(int recDir);
    void setSendingToken(bool value);
    void sendOwnToken();
    void newOwnToken();
    void setToken(TokenType type);
    void copyParentPositionTokens(int surfaceParent);
    void movePositionTokens(bool toTail);
    void clearPositionTokens(bool inHead);
    Phase phase;
    int followDir;
    int Lnumber;
    int downDir;
    int leftDir;
    int rightDir;
    int NumFinishedNeighbors;
    bool reachedSeedBound;
    bool hasComplained;
    int pullDir;
    int holdCount;
    bool startedOffSurface;
    int parentStage;
    int childStage;
    int ownTokenValue;
    bool hasLost;
    bool superLeader;
    int borderPasses;
    bool madeAgent;
    int id;

};
}


#endif // C
