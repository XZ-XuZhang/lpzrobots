/***************************************************************************
 *   Copyright (C) 2005-2009 by Robot Group Leipzig                        *
 *    martius@informatik.uni-leipzig.de                                    *
 *    fhesse@informatik.uni-leipzig.de                                     *
 *    der@informatik.uni-leipzig.de                                        *
 *    guettler@informatik.uni-leipzig.de                                   *
 *    jhoffmann@informatik.uni-leipzig.de                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *                                                                         *
 *   Informative Beschreibung der Klasse                                   *
 *                                                                         *
 *   $Log$
 *   Revision 1.5  2009-05-14 15:29:54  robot12
 *   bugfix: mutation change the oldGen, not the new!!! now fixed
 *
 *   Revision 1.4  2009/05/12 13:29:24  robot12
 *   some new function
 *   -> toString methodes
 *
 *   Revision 1.3  2009/05/11 14:08:51  robot12
 *   patch some bugfix....
 *
 *   Revision 1.2  2009/05/06 13:28:22  robot12
 *   some implements... Finish
 *
 *   Revision 1.1  2009/05/04 15:27:57  robot12
 *   rename of some files and moving files to other positions
 *    - SingletonGenAlgAPI has one error!!! --> is not ready now
 *
 *   Revision 1.2  2009/05/04 09:20:52  robot12
 *   some implements.. Finish --> first compile
 *
 *   Revision 1.1  2009/04/29 14:32:29  robot12
 *   some implements... Part4
 *
 *
 *
 ***************************************************************************/

#ifndef TEMPLATEVALUE_H_
#define TEMPLATEVALUE_H_

#include <string>

#include "IValue.h"

inline std::string doubleToString(double value) {
	char buffer[128];
	sprintf(buffer,"% .12lf",value);
	return buffer;
}

template<class Typ, std::string toString(Typ)=doubleToString>
class TemplateValue : public IValue {
public:
	TemplateValue(Typ value, std::string name = "templateValue") : IValue(name), m_value(value)  {}
	virtual ~TemplateValue()  {}

	inline Typ getValue(void)const {return m_value;}
	inline void setValue(Typ value) {m_value=value;}

	virtual IValue* operator*(const IValue& value)const {
		TemplateValue<Typ,toString>* newValue;

		const TemplateValue<Typ,toString>* castValue = dynamic_cast<const TemplateValue<Typ,toString>* >(&value);
		if(castValue==0)
			return 0;

		const Typ typeValue = castValue->getValue();
		newValue = new TemplateValue<Typ,toString>(m_value*typeValue);

		return newValue;
	}

	virtual operator std::string(void)const {
		return toString(m_value);
	}

protected:
	Typ m_value;

private:
	TemplateValue() : IValue() {}
};

#endif /* TEMPLATEVALUE_H_ */