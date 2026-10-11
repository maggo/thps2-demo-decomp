#ifndef COMPETITION_H
#define COMPETITION_H

struct CCompetition;

#endif // COMPETITION_H

#ifdef COMPETITION_DECLARE_ADDRESS_VIEWS
/** Opaque address views of COMPETITION's target-ordered text owners. */
extern char s_HeatOverBanner[];
extern char s_JudgesScoresTitle[];
extern char s_JudgeScoreRowFormat[];
extern char s_JudgeNumberFormat[];
extern char s_HeatScoreHeaderFormat[];
extern char s_ScoreFormat[];
extern char s_Congratulations[];
extern char s_YouScoredAllGolds[];
extern char s_YourAreTheTopProSkater[];
extern char s_WatchThisGetOffCouch[];
extern char s_CouchAndGoSkate[];
extern char s_YourThirdMedal[];
extern char s_YouJustMightBecome[];
extern char s_AnAverageSkater[];
extern char s_ProSkatersGetAllGolds[];
extern char s_CompetitionStandings[];
extern char s_PlaceColumnsHeader[];
extern char s_HeatLabel[];
extern char s_StringFormat[];
extern char s_Dash[];
extern char s_YouWinTheGold[];
extern char s_YouWinTheSilver[];
extern char s_YouWinTheBronze[];
extern char s_YouLose[];
extern char s_FirstPlaceFormat[];
extern char s_SecondPlaceFormat[];
extern char s_ThirdPlaceFormat[];
extern char s_OrdinalFormat[];
extern char s_HeatTitleFormat[];

/** Three competition medal-message records constructed at startup. */
extern SMedalMessage MedalMessage[3];

#undef COMPETITION_DECLARE_ADDRESS_VIEWS
#endif

#ifdef COMPETITION_DECLARE_OWNER_STATE_VIEW
/** Process-lifetime competition state owned by COMPETITION. */
extern CCompetition theCompetition;

#undef COMPETITION_DECLARE_OWNER_STATE_VIEW
#endif
