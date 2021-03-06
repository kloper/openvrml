//
// OpenVRML
//
// Copyright 2001  Henri Manson
// Copyright 2008  Braden McDaniel
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package vrml.field;

import vrml.Field;
import vrml.BaseNode;

/**
 * Represents a VRML SFNode field in Java.
 */
public class SFNode extends Field {
    private BaseNode node;

    /**
     * Construct a new SFNode field in OpenVRML using the given node.
     *
     * @param node VRML Node to create SFNode with.
     */
    static native long createPeer(BaseNode node);

    /**
     * Construct a default SFNode field.
     */
    public SFNode() {
        this(null);
    }

    /**
     * Initialize SFNode.node to correspond to the node in the peer.
     */
    static native BaseNode initNode(long peer);

    /**
     * Construct from a peer handle.
     */
    SFNode(long peer) {
        super(peer);
        this.node = SFNode.initNode(peer);
    }

    /**
     * Construct an SFNode field.
     *
     * @param node VRML Node to create SFNode with
     */
    public SFNode(BaseNode node) {
        super(createPeer(node));
        this.node = node;
    }

    /**
     * Create a shallow copy of the SFNode; the underlying BaseNode is
     * not copied.
     *
     * @return a shallow copy of the SFNode.
     */
    public Object clone() throws CloneNotSupportedException {
        final SFNode sfn = (SFNode) super.clone();
        sfn.node = this.node;
        return sfn;
    }

    /**
     * Get the VRML node stored in this SFNode.
     *
     * @return VRML node object
     */
    public BaseNode getValue() {
        return this.node;
    }

    private native void setPeerValue(BaseNode node);

    /**
     * Set the VRML node stored in this SFNode.
     *
     * @param node VRML node object
     */
    public void setValue(BaseNode node) {
        this.node = node;
        this.setPeerValue(node);
    }

    /**
     * Set the VRML node stored in this SFNode.
     *
     * @param node Existing ConstSFNode
     */
    public void setValue(ConstSFNode node) {
        this.setValue(node.getValue());
    }

    /**
     * Set the VRML node stored in this SFNode.
     *
     * @param node Existing SFNode
     */
    public void setValue(SFNode node) {
        this.setValue(node.getValue());
    }
}
