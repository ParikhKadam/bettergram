/*
This file is part of Bettergram.

For license and copyright information please follow this link:
https://github.com/bettergram/bettergram/blob/master/LEGAL
*/
#pragma once

#include "mtproto/dedicated_file_loader.h"

namespace MTP {
class Instance;
} // namespace MTP

namespace Core {

bool UpdaterDisabled();
void SetUpdaterDisabledAtStartup();

class Updater;

class UpdateChecker {
public:
	enum class State {
		None,
		Download,
		Ready,
	};
	using Progress = MTP::AbstractDedicatedLoader::Progress;

	UpdateChecker();

	rpl::producer<> checking() const;
	rpl::producer<> isLatest() const;
	rpl::producer<Progress> progress() const;
	rpl::producer<> failed() const;
	rpl::producer<> ready() const;

	void start(bool forceWait = false);
	void stop();
	void test();

	void setMtproto(const QPointer<MTP::Instance> &mtproto);

	State state() const;
	int already() const;
	int size() const;

private:
	const std::shared_ptr<Updater> _updater;

};

bool checkReadyUpdate();
void UpdateApplication();
QString countAlphaVersionSignature(uint64 version);

} // namespace Core
