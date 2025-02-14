/*
 * Copyright (C) 2020 Georg Zotti (based on F. Chereau's SimbadSearcher)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef HIPONLINEQUERY_HPP
#define HIPONLINEQUERY_HPP

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

//! @class HipOnlineReply
//! Contains all the information about a current HIP lookup query.
//! Instances of this class are generated by the HipOnlineQuery class.
class HipOnlineReply : public QObject
{
	Q_OBJECT

	friend class HipOnlineQuery;

public:
	//! Possible status for a Starnames query.
	enum HipQueryStatus
	{
		HipQueryQuerying,          //!< Starnames is still being queried.
		HipQueryErrorOccured,      //!< An error occured while looking up Starnames. Call getErrorString() for a description of the error.
		HipQueryFinished           //!< The query is over. The reply can be deleted.
	};
	Q_ENUM(HipQueryStatus)

	~HipOnlineReply() Q_DECL_OVERRIDE;

	//! Get the raw result HTML string from HIP search
	QString getResult() const {return htmlResult;}

	//! Get the current status.
	HipQueryStatus getCurrentStatus() const {return currentStatus;}

	//! Get a I18n string describing the current status. It can be used e.g for reporting in widgets.
	QString getCurrentStatusString() const;

	//! Get the error description string. Return empty string if no error occured.
	QString getErrorString() const {return errorString;}

	//! Explicitly delete the internal QNetworkReply. Must not be called from a QNetworkReply signal.
	void deleteNetworkReply();

signals:
	//! Triggered when the lookup status change.
	void statusChanged();

private slots:
	void httpQueryFinished();

private:
	//! Private constructor can be called by HipOnlineQuery only.
	HipOnlineReply(const QString& url, QNetworkAccessManager* mgr);

	const QString url;

	//! The reply used internally.
	QNetworkReply* reply;
	QNetworkAccessManager* netMgr;

	//! The HTML result of a query.
	QString htmlResult;

	//! Current query status.
	HipQueryStatus currentStatus;

	//! The error description. Empty if no errors occured.
	QString errorString;
};


//! @class HipOnlineQuery
//! Provides lookup features into an online service that accepts a Hipparcos number in the query string
class HipOnlineQuery : public QObject
{
	Q_OBJECT

public:
	//! Constructor
	//! @param baseURL complete URL like "https://mysite.org/lookForInfo.php?HIP=%1"
	//! It is allowed to initialize with an empty URL.
	HipOnlineQuery(QString baseURL, QObject* parent = Q_NULLPTR);

	//! set a new URL for the query. There must be a "%1" included, else no number or name can be added to the query!
	void setUrl(QString url);

	//! Lookup in an external starnames information site for object with catalog number.
	//! @param hipID the object ID. Only HIP IDs are supported.
	//! @return a new HipOnlineReply which is owned by the caller.
	HipOnlineReply* lookup(const int hipID);

	//! Lookup in an external information site for object with name.
	//! @param name the object name. Use getEnglishName() for a typical name.
	//! @return a new HipOnlineReply which is owned by the caller.
	HipOnlineReply* lookup(const QString name);

	//! Lookup in an external starnames information site for object with catalog number.
	//! @param url a new URL to use.
	//! @param hipID the object ID. Only HIP IDs are supported.
	//! @return a new HipOnlineReply which is owned by the caller.
	HipOnlineReply* lookup(const QString url, const int hipID);

	//! Lookup in an external information site for object with name.
	//! @param url a new URL to use.
	//! @param name the object name. Use getEnglishName() for a typical name.
	//! @return a new HipOnlineReply which is owned by the caller.
	HipOnlineReply* lookup(const QString url, const QString name);
private:
	//! The specific URL for the site like "https://mysite.org/lookForInfo.php?HIP="
	QString baseURL;
	//! The network manager used to query the website
	QNetworkAccessManager* networkMgr;
};

#endif /* HIPONLINEQUERY_HPP */
